/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   opr_rotate.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/02 21:30:13 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:46:21 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief with this function we define first top then the bottom element of the
 * stack by changing the value pointed in circular array. we use tmp
 * storage while we are swapping the values between the top and the bottom.
 * @note here my top will be the value inside my stack already. since we first
 * move the current top to tmp and then move top to top + 1 we are not doing a
 * overwrite into it.
 */
static void	rotate_stack(t_stack *stack)
{
	int	tmp;
	int	bottom;

	if (stack->current_size < 2)
		return ;
	tmp = stack->ring[stack->top];
	stack->top = (stack->top + 1) % stack->max_size;
	bottom = (stack->top + (stack->current_size - 1)) % stack->max_size;
	stack->ring[bottom] = tmp;
}

/**
 * @name
 * @brief applied rotate_stack function on stack b. prints the name of the
 * operation followed by the new line.
*/
void	rotate_a(t_stack *a)
{
	rotate_stack(a);
	ft_printf("ra\n");
}

/**
 * @name
 * @brief applied rotate_stack function on stack b. prints the name of the
 * operation followed by the new line.
*/
void	rotate_b(t_stack *b)
{
	rotate_stack(b);
	ft_printf("rb\n");
}

/**
 * @name
 * @brief applied rotate_stack function on a and b. prints the name of the
 * operation followed by the new line.
*/
void	rotate_ab(t_stack *a, t_stack *b)
{
	rotate_stack(a);
	rotate_stack(b);
	ft_printf("rr\n");
}
