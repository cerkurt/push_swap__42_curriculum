/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ranks_and_stacks.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 23:45:08 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 10:24:39 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @name
 * @brief a function that sorts an integer array in-place. it uses a temporary
 * storage to swap values if next is > current.
 */
void	sort_integer_array(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	int				tmp;

	if (size < 2)
		return ;
	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @name
 * @brief function that returns the index of the rank inside the array. if not
 * found returns (-1).
 */
int	find_index(int *sorted_table, unsigned int size, int value)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		if (sorted_table[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @name
 * @brief function that scans whole array and turns all the values into ranks
 * based on their magnitude. since the lowest element in my stack will be
 * different each time argument is given, rather than comparing their raw int
 * values i compare them as ranks to keep system highgly adaptive. this also
 * makes sorting and pushing as chunks easier.
 * @note in here we use i to only locate the value. because i as my index, just
 * tells the logical position inside my stack.
 */
void	values_to_ranks(t_stack *stack)
{
	int	*int_arr;
	int	i;
	int	j;

	int_arr = ft_calloc(stack->current_size, sizeof(int));
	if (!int_arr)
		error_exit();
	i = 0;
	while (i < stack->current_size)
	{
		int_arr[i] = position_to_value(stack, i);
		i++;
	}
	sort_integer_array(int_arr, stack->current_size);
	i = 0;
	while (i < stack->current_size)
	{
		j = find_index(int_arr, stack->current_size,
				position_to_value(stack, i));
		stack->ring[(stack->top + i) % stack->max_size] = j;
		if (j < 0)
			error_exit();
		i++;
	}
	free(int_arr);
}

/**
 * @name
 * @brief function that creates the stacks based on the size of the given
 * arguments. stack allocation hapeens once, and only inside the main function.
 */
void	create_stack(t_stack *stack, int max_size)
{
	stack->ring = ft_calloc(max_size, sizeof(int));
	if (!stack->ring)
		error_exit();
	stack->top = 0;
	stack->current_size = 0;
	stack->max_size = max_size;
}

/**
 * @name
 * @brief we fill the created stacks with the distiled argument sets. we simply
 * copy the int array arr into our circular array, ring.
 */
void	fill_stacks(t_stack *stack, int *arr, int size)
{
	int	i;

	if (size > stack->max_size)
		error_exit();
	i = 0;
	while (i < size)
	{
		stack->ring[i] = arr[i];
		i++;
	}
	stack->top = 0;
	stack->current_size = size;
}
