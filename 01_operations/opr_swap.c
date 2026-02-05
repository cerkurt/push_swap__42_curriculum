/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   opr_swap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 21:28:47 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:46:39 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief function that swaps top two element of the stack. we use temporary
 * storage to hold value during swap operation. while new top becomes old top +1
 * our old top becomes the current top + 1.
 */
static void	swap_numbers(t_stack *stack)
{
	int	tmp;
	int	i_top;
	int	i_next;

	if (stack->current_size < 2)
		return ;
	i_top = stack->top;
	i_next = (stack->top + 1) % stack->max_size;
	tmp = stack->ring[i_top];
	stack->ring[i_top] = stack->ring[i_next];
	stack->ring[i_next] = tmp;
}

/**
 * @name
 * @brief applied swap_numbers function on stack a. prints the name of the
 * operation followed by the new line.
 */
void	swap_a(t_stack *a)
{
	swap_numbers(a);
	ft_printf("sa\n");
}

/**
 * @name
 * @brief applied swap_numbers function on stack b. prints the name of the
 * operation followed by the new line.
 */
void	swap_b(t_stack *b)
{
	swap_numbers(b);
	ft_printf("sb\n");
}

/**
 * @name
 * @brief applied swap_numbers function on stack a and b. prints the name of the
 * operation followed by the new line.
 */
void	swap_a_and_b(t_stack *a, t_stack *b)
{
	swap_numbers(a);
	swap_numbers(b);
	ft_printf("ss\n");
}
