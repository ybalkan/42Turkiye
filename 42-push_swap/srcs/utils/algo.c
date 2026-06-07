/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:49:47 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:40:14 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

int	find_max_pos(t_node **stack)
{
	t_node	*tmp;
	int		max_val;
	int		max_pos;
	int		curr_pos;

	tmp = *stack;
	max_val = INT_MIN;
	max_pos = 0;
	curr_pos = 0;
	while (tmp)
	{
		if (tmp->value > max_val)
		{
			max_val = tmp->value;
			max_pos = curr_pos;
		}
		tmp = tmp->next;
		curr_pos++;
	}
	return (max_pos);
}

int	find_max_val(t_node *stack)
{
	int	max;

	max = stack->value;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}

int	find_min_pos(t_node *stack)
{
	int		min_val;
	int		min_pos;
	int		curr_pos;

	min_val = stack->value;
	min_pos = 0;
	curr_pos = 0;
	while (stack)
	{
		if (stack->value < min_val)
		{
			min_val = stack->value;
			min_pos = curr_pos;
		}
		stack = stack->next;
		curr_pos++;
	}
	return (min_pos);
}

void	ps_set_rank_indices(t_node *stack)
{
	t_node	*curr;
	t_node	*runner;
	int		rank;

	curr = stack;
	while (curr)
	{
		rank = 0;
		runner = stack;
		while (runner)
		{
			if (curr->value > runner->value)
				rank++;
			runner = runner->next;
		}
		curr->index = rank;
		curr = curr->next;
	}
}
