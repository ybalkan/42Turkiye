/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrotate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:49:21 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:44 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

static void	reverse_rotate(t_node **stack)
{
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = ps_get_last(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	(*stack)->prev = last;
	*stack = last;
}

void	rra(t_node **a, bool print, int *move_count)
{
	reverse_rotate(a);
	if (print)
	{
		write(1, "rra\n", 4);
		if (move_count)
		{
			move_count[0]++;
			move_count[9]++;
		}
	}
}

void	rrb(t_node **b, bool print, int *move_count)
{
	reverse_rotate(b);
	if (print)
	{
		write(1, "rrb\n", 4);
		if (move_count)
		{
			move_count[0]++;
			move_count[10]++;
		}
	}
}
