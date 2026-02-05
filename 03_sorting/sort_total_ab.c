/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_total_ab.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/24 20:53:15 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 23:52:21 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief function that gives passports to ranks in the stack based on the
 * boundries. our goal is to keep low ranks at the bottom of the stack b and
 * high ones at the top. so we start with defining our passport frame with 0 and
 * we start giving passport to first 20 ranks for stacks smaller than 100 ints.
 * if stack is larger than 100, we use passport frame of 40. we set push count
 * to 0 later to be increased in the caller function.
 */
void	define_pass(t_pass *f, int size)
{
	f->low = 0;
	f->max = size - 1;
	f->frame = size / 5;
	f->high = f->low + f->frame - 1;
	f->p_count = 0;
	f->scan = 0;
}

/**
 * @name
 * @brief after pushing to b is done with the first passport frame, i update the
 * frame simply setting the low on top of the old frame and shift the range
 * forward.
 */
void	update_pass(t_pass *f)
{
	if (f->high >= f->max)
	{
		f->p_count = 0;
		return ;
	}
	f->low = f->low + f->frame;
	f->high = f->high + f->frame;
	if (f->high > f->max)
		f->high = f->max;
	f->p_count = 0;
}

/**
 * @name
 * @brief to keep b organized, if the rank i push is in the first half of the
 * given passport frame, then i rotate b to keep small values at the bottom as
 * we always wanted to do since the start. if it is at the second half, then i
 * do not have to do anything, i keep pushing my next values.
 */
void	shape_b_after_push(t_stack *b, t_pass *f, int rank)
{
	if (rank < f->low + (f->frame / 2))
		rotate_b(b);
}

/**
 * @name
 * @brief after everything is done, in this function we actually perform the
 * passport scan and push. we keep lookin at the rank sitting at the logical
 * position of 0. if it is inside the given passport frame then we push it to
 * b. if not, we rotate a and check the next element. 
 */
void	scan_push_and_pass_update(t_stack *a, t_stack *b, t_pass *f)
{
	int	val;

	val = position_to_value(a, 0);
	if (val >= f->low && val <= f->high)
	{
		push_a_to_b(a, b);
		shape_b_after_push(b, f, val);
		f->p_count++;
		f->scan = 0;
		if (f->p_count == f->frame)
			update_pass(f);
		return ;
	}
	rotate_a(a);
	f->scan++;
	if (f->scan >= a->current_size)
	{
		update_pass(f);
		f->scan = 0;
	}
}

void	sort_ab(t_stack *a, t_stack *b)
{
	t_rocost	best_candidate;

	if (a->current_size <= 1)
		return ;
	if (a->current_size == 2)
		return (sort_two_a(a));
	if (a->current_size == 3)
		return (sort_three_a(a));
	if (a->current_size == 4)
		return (sort_four_a(a, b));
	if (a->current_size == 5)
		return (sort_five_a(a, b));
	if (a->current_size > 5)
	{
		insert_in_b(a, b);
		sort_three_a(a);
	}
	while (b->current_size > 0)
	{
		best_candidate = cheapest_move(a, b);
		apply_move_b_to_a(a, b, best_candidate);
	}
	final_rotate_a(a);
}
