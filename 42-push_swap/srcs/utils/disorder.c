/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:06:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:40:17 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

int	ps_get_disorder(t_node *stack)
{
	int		mistakes;
	t_node	*runner;

	mistakes = 0;
	while (stack)
	{
		runner = stack->next;
		while (runner)
		{
			if (stack->value > runner->value)
				mistakes++;
			runner = runner->next;
		}
		stack = stack->next;
	}
	return (mistakes);
}
