/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost_calculations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/17 17:19:49 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:47:06 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief fuction that gives us the cost of the rotations for given position, in
 * 		inside the stack size value.
 * @note here is the logic; if given position it located in the first half of
 * 		the total stack size, then number of cost is the current position index.
 * 		else, cost is cost - total size which gives us the signed value.
 * @note signed value here defines if i need to do rotate or reverse rotate. if
		cost is positive, then rotate. if negative then reverse rotate. voila!
 */
int	bring_to_top_cost(int pos, int size)
{
	int	rot_cost;

	rot_cost = 0;
	if (pos <= size / 2)
		rot_cost = pos;
	else
		rot_cost = pos - size;
	return (rot_cost);
}

/**
 * @name
 * @brief function that converts signed value of the cost, into its absolute val
 * 		to be used in safe comparisons later on.
*/
int	abs_val_cost(int move_cost)
{
	if (move_cost < 0)
		move_cost = -move_cost;
	return (move_cost);
}

/**
 * @name
 * @brief function that gives amount of combined rotations can be done for the
 * 		specific value in the stack.
 * @param cost_a signed value
 * @param cost_b signed value
 * @note we pass the cost as signed value but for the comparison, we need their
 * 		absolute value.
 */
int	combined_bring_to_top_cost(int cost_a, int cost_b)
{
	int	cmb_rot;

	cmb_rot = 0;
	if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
	{
		if (abs_val_cost(cost_a) > abs_val_cost(cost_b))
			cmb_rot = abs_val_cost(cost_a);
		else
			cmb_rot = abs_val_cost(cost_b);
	}
	else
		cmb_rot = abs_val_cost(cost_a) + abs_val_cost(cost_b);
	return (cmb_rot);
}

t_rocost	cost_check(int pos_a, int pos_b, t_stack *a, t_stack *b)
{
	t_rocost	c;

	c.rocost_a = bring_to_top_cost(pos_a, a->current_size);
	c.rocost_b = bring_to_top_cost(pos_b, b->current_size);
	c.rocost_total = combined_bring_to_top_cost(c.rocost_a, c.rocost_b) + 1;
	c.rank = 0;
	return (c);
}
