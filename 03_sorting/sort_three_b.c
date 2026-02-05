/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_three_b.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 23:00:10 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:49:33 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief minimal sorting case of 3 integers, if they are sorted in 321 format.
 * 		to sort this stack in ascending order we first need to swap 3 and 2, and
 * 		reverse rotate to make 1 on top.
 */
static void	sort_case_321_b(t_stack *b)
{
	swap_b(b);
	reverse_rotate_b(b);
}

/**
 * @name
 * @brief minimal sorting case of 3 integers, if they are sorted in 132 format.
 * 		to sort this stack in ascending order we first need to reverse rotate to
 * 		bring 2 on top, then swap values and sort the stack.
 */
static void	sort_case_132_b(t_stack *b)
{
	reverse_rotate_b(b);
	swap_b(b);
}

/**
 * @name
 * @brief applied version of different sorting cases inside stack b.
 */
void	sort_three_b(t_stack *b)
{
	int	num0;
	int	num1;
	int	num2;

	if (b->current_size != 3)
		return ;
	num0 = b->ring[b->top];
	num1 = b->ring[(b->top + 1) % b->max_size];
	num2 = b->ring[(b->top + 2) % b->max_size];
	if (num0 < num1 && num1 < num2)
		return ;
	else if (num0 > num1 && num1 < num2 && num0 < num2)
		swap_b(b);
	else if (num0 > num1 && num1 > num2)
		sort_case_321_b(b);
	else if (num0 > num1 && num1 < num2 && num0 > num2)
		rotate_b(b);
	else if (num0 < num1 && num1 > num2 && num0 < num2)
		sort_case_132_b(b);
	else if (num0 < num1 && num1 > num2 && num0 > num2)
		reverse_rotate_b(b);
}
