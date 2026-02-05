/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/30 14:08:59 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/30 15:39:12 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/**
 * @name
 * @brief is a set of data (container) to use in verious operations
 * in my push_swap.
 * @param ring is my array of integers which will be swapped between and
 * allocated accoringly. aka allocated array of length max_size
 * @param top is the index of the top element in the array. For example
 * top index of the stack if always 0. We have logical top and orgers in
 * circular arrays and thanks to this logic, we do not have to memmove of
 * the indexes like a linear array.
 * @param current_size number of valid elements currently in the stack. This
 * value changes during the runtime of the program.
 * @param max_size shows how much space to be allocated for the whole array.
 * This value does not change unless we reallocate. capacity of the circular
 * buffer and it is fixed, never changes.
 * @note 1. a->data[0] is same with (*a).data[0]. It lets access a field of a
 * struct through a pointer.
 * @note 2. -> symbol doesnt make the struct a linked list. To have a linked
 * list, there should be a pointer to another struct of the same type.
 */
typedef struct s_stack
{
	int	*ring;
	int	top;
	int	current_size;
	int	max_size;
}	t_stack;

/**
 * @name
 * @brief is a set of data (container) to calculate move costs and
 * store its data before I do any operations.
 * @param cost_a amount of moves that i need to make in stack_a for certain
 * element to move.
 * @param cost_b amount of moves that i need to make in stack_b for certain
 * element to move.
 * @param cost_total is the sum of the move counts in both stacks for certain
 * element to move. additionally includes push cost as + 1. because we
 * wont be rotating the elements if we are not gonna make them pushed
 * in other stack.
 * @param rank indicates the element chosen based on the cost calculation.
 * @note signed costs are intentional to encode the direction of the move. 
 */
typedef struct s_rocost
{
	int	rocost_a;
	int	rocost_b;
	int	rocost_total;
	int	rank;
}	t_rocost;

/**
 * @name
 * @brief my struct that i use to find best element to move from b to a.
 */
typedef struct seek_target
{
	int	i;
	int	min_val;
	int	min_pos;
	int	best_val;
	int	best_pos;
}	t_seek_target;

/**
 * @name
 * @brief this struct is the officer of my passport control policy :) i give
 * permissions to certain values to go stay in b, or they keep staying in a
 * until their time comes to be pushed.
 */
typedef struct s_pass
{
	int	low;
	int	high;
	int	max;
	int	frame;
	int	p_count;
	int	scan;
}	t_pass;

// rotate operations

void		rotate_a(t_stack *a);
void		rotate_b(t_stack *b);
void		rotate_ab(t_stack *a, t_stack *b);

// reverse rotate operations

void		reverse_rotate_a(t_stack *a);
void		reverse_rotate_b(t_stack *b);
void		reverse_rotate_ab(t_stack *a, t_stack *b);

// push operations

void		push_a_to_b(t_stack *a, t_stack *b);
void		push_b_to_a(t_stack *b, t_stack *a);

// swap operations

void		swap_a(t_stack *a);
void		swap_b(t_stack *b);
void		swap_a_and_b(t_stack *a, t_stack *b);

// stack sorting & organizing functions

void		sort_two_a(t_stack *a);
void		sort_two_b(t_stack *b);
void		sort_three_a(t_stack *a);
void		sort_three_b(t_stack *b);
void		sort_ab(t_stack *a, t_stack *b);
void		insert_in_b(t_stack *a, t_stack *b);
void		sort_four_a(t_stack *a, t_stack *b);
void		sort_five_a(t_stack *a, t_stack *b);

// stack search and move calculation functions

void		final_rotate_a(t_stack *a);
int			abs_val_cost(int move_cost);
int			insert_in_a(t_stack *a, int rank);
int			bring_to_top_cost(int pos, int size);
t_rocost	cheapest_move(t_stack *a, t_stack *b);
int			position_to_value(t_stack *stack, int pos);
int			value_to_position(t_stack *stack, int val);
int			combined_bring_to_top_cost(int cost_a, int cost_b);
t_rocost	cost_check(int pos_a, int pos_b, t_stack *a, t_stack *b);
void		apply_move_b_to_a(t_stack *a, t_stack *b, t_rocost cost);

// parsing & argument handling functions

void		error_exit(void);
void		update_pass(t_pass *f);
int			is_a_sorted(t_stack *a);
void		value_free_and_exit(int *val);
void		values_to_ranks(t_stack *stack);
void		define_pass(t_pass *f, int size);
void		free_in_main(t_stack *a, t_stack *b);
void		*ft_array_free(char **arr, size_t count);
void		create_stack(t_stack *stack, int volume);
void		sort_integer_array(int *tab, unsigned int size);
void		free_and_error_exit(char **values, int arr_size);
void		ultimate_free(char **values, int *val, int size);
void		fill_stacks(t_stack *stack, int *array, int size);
int			string_to_valid_value(const char *s, int *output);
void		shape_b_after_push(t_stack *b, t_pass *f, int rank);
int			*single_argument_parsing(const char *s, int *arr_size);
int			find_index(int *sorted_table, unsigned int size, int value);
void		scan_push_and_pass_update(t_stack *a, t_stack *b, t_pass *f);
int			*multiple_arguments_parsing(int argc, char **argv, int *arr_size);

#endif