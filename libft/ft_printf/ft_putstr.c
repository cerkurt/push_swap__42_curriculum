/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/21 14:53:11 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/23 20:17:49 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @name ft_putstr
 * @brief Writes a string to the standard output. If the string is NULL,
 *               it prints "(null)". This function is used to handle the %s
 *               specifier in ft_printf.
 * @param str The string to write.
 * @return The number of characters written.
 */
size_t	ft_putstr_printf(char *str)
{
	size_t	i;

	if (!str)
		return (ft_putstr_printf("(null)"));
	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}
