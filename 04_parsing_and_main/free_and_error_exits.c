/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_error_exits.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/27 21:33:13 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 15:38:52 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @name
 * @brief function write error to stdout. 
 */
void	error_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

/**
 * @name
 * @brief function write error to stdout after freeing the allocated stuff.
 */
void	free_and_error_exit(char **values, int arr_size)
{
	ft_array_free(values, arr_size);
	error_exit();
}

/**
 * @name
 * @brief function makes all the free process at one time. freeing the value,
 * freeing the array and doing error exit.
 */
void	ultimate_free(char **values, int *val, int size)
{
	free(val);
	ft_array_free(values, size);
	error_exit();
}

/**
 * @name
 * @brief function that frees the value and exots with error.
 */
void	value_free_and_exit(int *val)
{
	free(val);
	error_exit();
}

/**
 * @name
 * @brief helper function to save some lines in main. frees both stacks.
 */
void	free_in_main(t_stack *a, t_stack *b)
{
	free(a->ring);
	free(b->ring);
}
