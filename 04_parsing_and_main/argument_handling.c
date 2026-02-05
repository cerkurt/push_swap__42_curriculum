/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argument_handling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 20:00:21 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 15:29:28 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @name
 * @brief simple function that calculates our array size, which is the amount
 * of input.
 */
static int	array_size(char **values)
{
	int	i;

	i = 0;
	while (values[i])
		i++;
	return (i);
}

/**
 * @name
 * @a function checks for the duplicated while also filling the array with the
 * given values. if there is any duplicate, we return -1 and later we use this
 * result to validate that the inputs are unique or not.
 */
static int	array_fill_dup_check(int *arr, char **values, int n)
{
	int	i;
	int	j;
	int	output;

	i = 0;
	while (i < n)
	{
		if (!string_to_valid_value(values[i], &output))
			return (-1);
		arr[i] = output;
		j = 0;
		while (j < i)
		{
			if (arr[j] == output)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @name
 * @brief this functions handles the argument given between the " ". using our
 * ft_split we split the given string into sub strings, and check if we ever
 * have any duplicates.
 * @param s is the string given between " ".
 * @param arr_size is the lenght of the array, calculated with the helper func.
 */
int	*single_argument_parsing(const char *s, int *arr_size)
{
	char	**values;
	int		*val;

	values = ft_split(s, ' ');
	if (!values)
		error_exit();
	*arr_size = array_size(values);
	if (*arr_size == 0)
		free_and_error_exit(values, *arr_size);
	val = ft_calloc(*arr_size, sizeof(int));
	if (!val)
		free_and_error_exit(values, *arr_size);
	if (array_fill_dup_check(val, values, *arr_size) == -1)
		ultimate_free(values, val, *arr_size);
	ft_array_free(values, *arr_size);
	return (val);
}

/**
 * @name
 * @brief this function checks duplicates internally, after turning every given
 * argv into valid values using atoi conversion and compares each new value with
 * the previous ones. if any match we free the value written so far and exit
 * with the error path.
 * @param argc is, obvious. the argc.
 * @param argv is again pretty much clear.
 * @param arr_size is the lenght of the array, calculated with the helper func.
 */
int	*multiple_arguments_parsing(int argc, char **argv, int *arr_size)
{
	int	*val;
	int	i;
	int	j;
	int	output;

	*arr_size = argc - 1;
	val = ft_calloc(*arr_size, sizeof(int));
	if (!val)
		error_exit();
	i = 1;
	while (i < argc)
	{
		if (!string_to_valid_value(argv[i], &output))
			value_free_and_exit(val);
		val[i - 1] = output;
		j = 0;
		while (j < i - 1)
		{
			if (val[j] == val[i - 1])
				value_free_and_exit(val);
			j++;
		}
		i++;
	}
	return (val);
}

/**
 * @name
 * @brief this function checks if a is already sorted at the start or not. we do
 * this simply comparing element with the next one. if it is sorted we return 1,
 * if not we return 0 and based on this result we start sorting the a or do not
 * touch it at all.
 */
int	is_a_sorted(t_stack *a)
{
	int	i;
	int	cur_val;
	int	next_val;

	if (a->current_size < 2)
		return (1);
	i = 0;
	while (i < a->current_size - 1)
	{
		cur_val = position_to_value(a, i);
		next_val = position_to_value(a, i + 1);
		if (cur_val > next_val)
			return (0);
		i++;
	}
	return (1);
}
