/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:26:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:43:59 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	ps_free_all(t_node **stack)
{
	t_node	*curr;
	t_node	*tmp;

	if (!stack || !*stack)
		return ;
	curr = *stack;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	*stack = NULL;
}

void	ps_error_exit(t_node **stack_a, t_node **stack_b)
{
	if (stack_a)
		ps_free_all(stack_a);
	if (stack_b)
		ps_free_all(stack_b);
	write(2, "Error\n", 6);
	exit(1);
}
