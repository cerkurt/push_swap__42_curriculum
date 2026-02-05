/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/26 18:14:33 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 15:34:42 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @name
 * @brief this is a bit safe version of ft_atoi. i have added couple of extras
 * like doing error exit if string is empty or if it contains any element that
 * is not a digit or beyond the limits.
 */
int	string_to_valid_value(const char *s, int *output)
{
	int		sign;
	long	result;

	sign = 1;
	if (*s == '\0')
		return (0);
	if (*s == '-' || *s == '+')
	{
		if (*(s++) == '-')
			sign = -1;
	}
	if (!ft_isdigit(*s))
		return (0);
	result = 0;
	while (ft_isdigit(*s))
	{
		result = result * 10 + *(s++) - '0';
		if ((sign == -1 && (result * sign < INT_MIN))
			|| (sign == 1 && (result * sign > INT_MAX)))
			return (0);
	}
	if (*s != '\0')
		return (0);
	*output = (int)(result * sign);
	return (1);
}

/**
 * @name
 * @brief same helper function used in ft_split. it helps us to free allocated
 * array so far, if we encounter any error before completing the all.
 */
void	*ft_array_free(char **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
