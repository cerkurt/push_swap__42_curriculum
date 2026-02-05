/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   apply_calculated_moves.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/22 10:41:14 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:46:58 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief helper function that applies the mutual rotations in the correct
 * directions, based on the outcome of the cost calculations. negative means
 * reverse_rotate and positive means rotate.
 * @note we can only do mutual rotations, if the cost outcomes of the both
 * stacks have the same sign value. (both pos or both neg)
 */
static void	apply_mutual_rotations(t_stack *a, t_stack *b, t_rocost *cost)
{
	while (cost->rocost_a > 0 && cost->rocost_b > 0)
	{
		rotate_ab(a, b);
		cost->rocost_a--;
		cost->rocost_b--;
	}
	while (cost->rocost_a < 0 && cost->rocost_b < 0)
	{
		reverse_rotate_ab(a, b);
		cost->rocost_a++;
		cost->rocost_b++;
	}
}

/**
 * @name
 * @brief helper function that applies solo roations of stack_a, in the correct
 * directions, based on the outcome of the cost calculations. negative means
 * reverse_rotate and positive means rotate.
 * @param cost is the "key" that lets us to access certain sections in struct.
 * also is the result we get from "bing_to_top" function.
 */
static void	leftover_rotations_a(t_stack *a, t_rocost *cost)
{
	while (cost->rocost_a > 0)
	{
		rotate_a(a);
		cost->rocost_a--;
	}
	while (cost->rocost_a < 0)
	{
		reverse_rotate_a(a);
		cost->rocost_a++;
	}
}

/**
 * @name
 * @brief helper function that applies solo roations of stack_b, in the correct
 * directions, based on the outcome of the cost calculations. negative means
 * reverse_rotate and positive means rotate.
 * @param cost is the "key" that lets us to access certain sections in struct.
 * also is the result we get from "bing_to_top" function.
 */
static void	leftover_rotations_b(t_stack *b, t_rocost *cost)
{
	while (cost->rocost_b > 0)
	{
		rotate_b(b);
		cost->rocost_b--;
	}
	while (cost->rocost_b < 0)
	{
		reverse_rotate_b(b);
		cost->rocost_b++;
	}
}

/** 
 * @name
 * @brief function that applies required moves while inserting a number from
 * stack_b to stack_a.
 * @note the reason we do not cost pass it as pointer to the structs is, in this
 * function, we want cost to be consumed and used like a regular int value to be
 * used in the sequence of lines. for example after doing 5 mutual rotations if
 * i have 3 left in a, then i can do 3 solo rotations in stack_a. if i pass it
 * as *cost, then i will never be able to modify the original value and always
 * do 5 mutual and 5 solo rotations.
*/
void	apply_move_b_to_a(t_stack *a, t_stack *b, t_rocost cost)
{
	apply_mutual_rotations(a, b, &cost);
	leftover_rotations_a(a, &cost);
	leftover_rotations_b(b, &cost);
	push_b_to_a(b, a);
}

/**
 * @name
 * @brief function that adjusts the final touches in stack a, to make it fully
 * sorted at the end. we have a value, (which is the smallest) and we want place
 * it on the top of the stack. here we do the rotatons again based on the sign
 * of the cost.
 * @note pos = value_to_position(a, 0); this function tells us there is rank 0
 * currently in the stack and ased on its position we calculate to which
 * direction and how many rotations we should do to bring it to position 0.
 */
void	final_rotate_a(t_stack *a)
{
	int	pos;
	int	cost;

	pos = value_to_position(a, 0);
	if (pos < 0)
		return ;
	cost = bring_to_top_cost(pos, a->current_size);
	while (cost > 0)
	{
		rotate_a(a);
		cost--;
	}
	while (cost < 0)
	{
		reverse_rotate_a(a);
		cost++;
	}
}
