/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_four_five_a.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 20:00:20 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:49:05 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief rotates stack a, based on the cost calculation of the certain position
 * inside the stack. if positive rotate, if negative reverse_rotate.
 */
static void	rotate_a_to_top(t_stack *a, int pos)
{
	int	cost;

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

/**
 * @name
 * @brief function that prepares an element in stack a to be pushed in stack b.
 * we prepare a by simply getting the position of the rank, then calculate the
 * move cost inside rotate_a_to_top and end with pushing that element to the
 * stack b.
 */
static void	push_rank_to_b(t_stack *a, t_stack *b, int rank)
{
	int	pos;

	pos = value_to_position(a, rank);
	if (pos < 0)
		error_exit();
	rotate_a_to_top(a, pos);
	push_a_to_b(a, b);
}

/**
 * @name
 * @brief when a current_size is 4, we start with pushing the rank 0 to b.
 * because when we instert it back, we want it to be on the top of the stack a.
 * then we sort remaining 3 values in a and insert back from a to b based on the
 * cheapest way in insertion and rotate a finally if it is necessary.
 */
void	sort_four_a(t_stack *a, t_stack *b)
{
	t_rocost	best_move;

	if (a->current_size != 4)
		return ;
	push_rank_to_b(a, b, 0);
	sort_three_a(a);
	while (b->current_size > 0)
	{
		best_move = cheapest_move(a, b);
		apply_move_b_to_a(a, b, best_move);
	}
	final_rotate_a(a);
}

/**
 * @name
 * @brief here we push rank 0 and 1 to b becuase we want them back later on top.
 * but, here is the trick: after pushing these two values, if the top one is
 * rank 0, we swap b because when inserting back, we want the smallest value to
 * be on top. we sort remaining three vaues in a and insert back from a to b
 * based on the cheapest way in insertion and rotate a finally if it is
 * necessary.
 */
void	sort_five_a(t_stack *a, t_stack *b)
{
	t_rocost	best_move;

	if (a->current_size != 5)
		return ;
	push_rank_to_b(a, b, 0);
	push_rank_to_b(a, b, 1);
	if (b->current_size == 2 && position_to_value(b, 0) == 0)
		swap_b(b);
	sort_three_a(a);
	while (b->current_size > 0)
	{
		best_move = cheapest_move(a, b);
		apply_move_b_to_a(a, b, best_move);
	}
	final_rotate_a(a);
}

/**
 * @name
 * @brief this function is used while inserting elements to stack b while
 * current_size of stack a is bigger than 5. instead of blindly pushing, we push
 * with some boundries so we have almost organized stack b without getting
 * obsessed with making it fully structured. this helps us to avoid unnecessary
 * rotations in stack b and keep b clean at the same time.
 * @note this function is here due to amount of function limitations inside a
 * file. it is normally part of "sort_total_ab.c" file.
 */
void	insert_in_b(t_stack *a, t_stack *b)
{
	t_pass	f;

	define_pass(&f, a->current_size);
	while (a->current_size > 3)
		scan_push_and_pass_update(a, b, &f);
}
