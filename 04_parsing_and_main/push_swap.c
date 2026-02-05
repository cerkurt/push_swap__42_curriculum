/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 15:44:43 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 14:58:45 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*int_array;
	int		arr_size;
	t_stack	a;
	t_stack	b;

	if (argc <= 1)
		return (0);
	if (argc == 2)
		int_array = single_argument_parsing(argv[1], &arr_size);
	if (argc > 2)
		int_array = multiple_arguments_parsing(argc, argv, &arr_size);
	create_stack(&a, arr_size);
	create_stack(&b, arr_size);
	fill_stacks(&a, int_array, arr_size);
	free(int_array);
	values_to_ranks(&a);
	if (is_a_sorted(&a))
	{
		free_in_main(&a, &b);
		return (0);
	}
	sort_ab(&a, &b);
	free_in_main(&a, &b);
	return (0);
}
