/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   opr_push.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 21:30:29 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:45:34 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief function to push the top element of the stack a to top of stack b. No
 * cost calculations are applied because if element is brought to top to be
 * pushed, calculations are already done.
 * @note we only redefine the top of the a and top of the b while increasing and
 * decreasing the sizes of the both stacks. for example after push, top of a,
 * actually is the top + 1 in the circle while size is being decreased. but for
 * b, top is being top - 1 because we are inserting a new element before the
 * cureent top while size is being increased.
 */
void	push_a_to_b(t_stack *a, t_stack *b)
{
	int	push_value;

	if (a->current_size == 0)
		return ;
	push_value = a->ring[a->top];
	a->top = (a->top + 1) % a->max_size;
	a->current_size--;
	b->top = ((b->top - 1) + b->max_size) % b->max_size;
	b->ring[b->top] = push_value;
	b->current_size++;
	ft_printf("pb\n");
}

/**
 * @name
 * @brief function to push the top element of the stack b to top of stack a. No
 * cost calculations are applied because if element is brought to top to be
 * pushed, calculations are already done.
 * @note we only redefine the top of the b and top of the a while increasing and
 * decreasing the sizes of the both stacks. for example after push, top of b,
 * actually is the top + 1 in the circle while size is being decreased. but for
 * a, top is being top - 1 because we are inserting a new element before the
 * cureent top while size is being increased.
 */
void	push_b_to_a(t_stack *b, t_stack *a)
{
	int	push_value;

	if (b->current_size == 0)
		return ;
	push_value = b->ring[b->top];
	b->top = (b->top + 1) % b->max_size;
	b->current_size--;
	a->top = ((a->top - 1) + a->max_size) % a->max_size;
	a->ring[a->top] = push_value;
	a->current_size++;
	ft_printf("pa\n");
}
