/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_two_ab.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 23:00:10 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:50:40 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief minimal sorting function of two integers in stack a. returns without
 * doing noting if stack current_size is not 2. if top of the stack is
 * smaller than the next number in the stack, then simply we swap the values.
 */
void	sort_two_a(t_stack *a)
{
	int	num0;
	int	num1;

	if (a->current_size != 2)
		return ;
	num0 = a->ring[a->top];
	num1 = a->ring[(a->top + 1) % a->max_size];
	if (num0 > num1)
		swap_a(a);
}

/**
 * @name
 * @brief minimal sorting function of two integers in stack b. returns without
 * doing noting if stack current_size is not 2. if top of the stack is smaller
 * than the next number in the stack, then simply we swap the values.
 */
void	sort_two_b(t_stack *b)
{
	int	num0;
	int	num1;

	if (b->current_size != 2)
		return ;
	num0 = b->ring[b->top];
	num1 = b->ring[(b->top + 1) % b->max_size];
	if (num0 > num1)
		swap_b(b);
}
