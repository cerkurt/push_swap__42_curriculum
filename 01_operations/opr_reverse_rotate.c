/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   opr_reverse_rotate.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 10:51:17 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:46:02 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief with this function we redefine first the bottom then the top elements
 * of the stack by changing the value pointed in circular array. we use tmp
 * storage while we are swapping the values between bottom and the top.
 * @note bottom depends on how many elements exist: size. top depends on the
 * logical place inside the stack. therefor when calculating the new top we wrap
 * based on the volume so we do not ovverite already living slot inside the
 * stack.
 */
static void	reverse_rotate_stack(t_stack *stack)
{
	int	tmp;
	int	bottom;

	if (stack->current_size < 2)
		return ;
	bottom = ((stack->top + (stack->current_size - 1)) % stack->max_size);
	tmp = stack->ring[bottom];
	stack->top = (stack->top - 1 + stack->max_size) % stack->max_size;
	stack->ring[stack->top] = tmp;
}

/**
 * @name
 * @brief applied reverse_rotate_stack function on stack a. prints the name of
 *the operation at the end, followed by a new line.
 */
void	reverse_rotate_a(t_stack *a)
{
	reverse_rotate_stack(a);
	ft_printf("rra\n");
}

/**
 * @name
 * @brief applied reverse_rotate_stack function on stack b. prints the name of
 *the operation at the end, followed by a new line.
 */
void	reverse_rotate_b(t_stack *b)
{
	reverse_rotate_stack(b);
	ft_printf("rrb\n");
}

/**
 * @name
 * @brief applied reverse_rotate_stack function on together on stack a and b.
 * prints the name of the operation at the end, followed by a new line.
 */
void	reverse_rotate_ab(t_stack *a, t_stack *b)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	ft_printf("rrr\n");
}
