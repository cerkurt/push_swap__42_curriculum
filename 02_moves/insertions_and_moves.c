/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   insertions_and_moves.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cerkurt <cerkurt@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/18 12:15:31 by cerkurt       #+#    #+#                 */
/*   Updated: 2025/12/29 18:47:48 by cerkurt       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/**
 * @name
 * @brief function that gives us the value of the nuumber of the given position.
 * shortly, answers our question about: which rank is currently sitting in the
 * position pos of the stack?
 */
int	position_to_value(t_stack *stack, int pos)
{
	return (stack->ring[(stack->top + pos) % stack->max_size]);
}

/**
 * @name
 * @brief function that gives us the position of the given rank. shortly answers
 * the question about: well, i have rank 5 yes but where is it inside the stack?
 * later on we use this results to apply certain moves accross our stacks. we
 * simply scan inside the stack using our pos = value_to_position(a, 0); until
 * we find a match with our value in question.
 */
int	value_to_position(t_stack *stack, int val)
{
	int	i;

	i = 0;
	while (i < stack->current_size)
	{
		if (position_to_value(stack, i) == val)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @name
 * @brief function that scans the stack_a, seeks for a best place in stack_a to
 * insert the upcoming candidate number. we start assuming our min and best
 * values are int_max, as a start point for comparison. we can also think this
 * as a worst case assumption. here i say okay at best case i am gonna do INTMAX
 * amount of rotations. after that any number coming during the loop will be
 * updated as the smaller one.
 * @note if we start our assumption with int_min, since any number is always
 * bigger int_min, condition will never be fulfilled. 
 */
int	insert_in_a(t_stack *a, int rank)
{
	t_seek_target	s;
	int				val;

	s.i = 0;
	s.min_val = INT_MAX;
	s.best_val = INT_MAX;
	s.min_pos = 0;
	s.best_pos = 0;
	while (s.i < a->current_size)
	{
		val = position_to_value(a, s.i++);
		if (val < s.min_val)
		{
			s.min_val = val;
			s.min_pos = s.i - 1;
		}
		if (val > rank && val < s.best_val)
		{
			s.best_val = val;
			s.best_pos = s.i - 1;
		}
	}
	if (s.best_val == INT_MAX)
		return (s.min_pos);
	return (s.best_pos);
}

/**
 * @name
 * @brief function that finds the cheapest move in stack_b, to be pushed to
 * stack_a. i am trying to keep a almost perfectly sorted while inserting
 * numbers from b to a.
 * @note we assume the number of the moves (aka my aetate cost) is equal to
 * value of int max. after that, any smaller number of cost value will be
 * assigned to my best_move.
 * @note to pick the candidate rank, we calculate its logical position in
 * stack_b and later use this rank to calculate its cost to bring that value to
 * the top. (well, if we are not pushing at the end, when why we would chose a
 * candidate, right?)
 */
t_rocost	cheapest_move(t_stack *a, t_stack *b)
{
	t_rocost	best_move;
	t_rocost	candidate_cost;
	int			index_b;
	int			candidate_rank;

	best_move.rocost_total = INT_MAX;
	index_b = 0;
	while (index_b < b->current_size)
	{
		candidate_rank = position_to_value(b, index_b);
		candidate_cost = cost_check(insert_in_a(a, candidate_rank),
				index_b, a, b);
		candidate_cost.rank = candidate_rank;
		if (candidate_cost.rocost_total < best_move.rocost_total)
			best_move = candidate_cost;
		index_b++;
	}
	return (best_move);
}
