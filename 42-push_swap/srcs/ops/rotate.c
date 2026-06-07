/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:49:19 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:41 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "ops.h"

static void	rotate(t_node **stack)
{
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = ps_get_last(*stack);
	last->next = *stack;
	(*stack)->prev = last;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

void	ra(t_node **a, bool print, int *move_count)
{
	rotate(a);
	if (print)
	{
		write(1, "ra\n", 3);
		if (move_count)
		{
			move_count[0]++;
			move_count[6]++;
		}
	}
}

void	rb(t_node **b, bool print, int *move_count)
{
	rotate(b);
	if (print)
	{
		write(1, "rb\n", 3);
		if (move_count)
		{
			move_count[0]++;
			move_count[7]++;
		}
	}
}
