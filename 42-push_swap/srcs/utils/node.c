/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 21:33:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:40:21 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

t_node	*ps_node_new(int value)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = -1;
	new->pos = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ps_node_add_back(t_node **stack, t_node *new)
{
	t_node	*last;

	if (!stack || !new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ps_get_last(*stack);
	last->next = new;
	new->prev = last;
}
