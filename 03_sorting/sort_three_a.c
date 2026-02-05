/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_three_a.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 23:00:10 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:49:21 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief minimal sorting case of 3 integers, if they are sorted in 321 format.
 * 		to sort this stack in ascending order we first need to swap 3 and 2, and
 * 		reverse rotate to make 1 on top.
 */
static void	sort_case_321_a(t_stack *a)
{
	swap_a(a);
	reverse_rotate_a(a);
}

/**
 * @name
 * @brief minimal sorting case of 3 integers, if they are sorted in 132 format.
 * 		to sort this stack in ascending order we first need to reverse rotate to
 * 		bring 2 on top, then swap values and sort the stack.
 */
static void	sort_case_132_a(t_stack *a)
{
	reverse_rotate_a(a);
	swap_a(a);
}

/**
 * @name
 * @brief applied version of different sorting cases inside stack a. funtion
 * calls different sortcases based on how ordered the stack is. 
 */
void	sort_three_a(t_stack *a)
{
	int	num0;
	int	num1;
	int	num2;

	if (a->current_size != 3)
		return ;
	num0 = a->ring[a->top];
	num1 = a->ring[(a->top + 1) % a->max_size];
	num2 = a->ring[(a->top + 2) % a->max_size];
	if (num0 < num1 && num1 < num2)
		return ;
	else if (num0 > num1 && num1 < num2 && num0 < num2)
		swap_a(a);
	else if (num0 > num1 && num1 > num2)
		sort_case_321_a(a);
	else if (num0 > num1 && num1 < num2 && num0 > num2)
		rotate_a(a);
	else if (num0 < num1 && num1 > num2 && num0 < num2)
		sort_case_132_a(a);
	else if (num0 < num1 && num1 > num2 && num0 > num2)
		reverse_rotate_a(a);
}
