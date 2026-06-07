/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:49:14 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:37 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

static void	push(t_node **src, t_node **dst)
{
	t_node	*tmp;

	if (!*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	tmp->next = *dst;
	if (*dst)
		(*dst)->prev = tmp;
	*dst = tmp;
	(*dst)->prev = NULL;
}

void	pa(t_node **a, t_node **b, bool print, int *move_count)
{
	push(b, a);
	if (print)
	{
		write(1, "pa\n", 3);
		if (move_count)
		{
			move_count[0]++;
			move_count[4]++;
		}
	}
}

void	pb(t_node **a, t_node **b, bool print, int *move_count)
{
	push(a, b);
	if (print)
	{
		write(1, "pb\n", 3);
		if (move_count)
		{
			move_count[0]++;
			move_count[5]++;
		}
	}
}
