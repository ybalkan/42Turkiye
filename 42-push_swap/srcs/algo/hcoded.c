/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hcoded.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:22:21 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:40:38 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "ops.h"

void	sort_three(t_node **a, int *move_count)
{
	int	max;

	if (ps_is_sorted(*a))
		return ;
	max = find_max_val(*a);
	if ((*a)->value == max)
		ra(a, true, move_count);
	else if ((*a)->next->value == max)
		rra(a, true, move_count);
	if ((*a)->value > (*a)->next->value)
		sa(a, true, move_count);
}

void	ps_sort_small(t_node **a, t_node **b, int *move_count)
{
	while (ps_get_size(*a) > 3 && !ps_is_sorted(*a))
		ps_push_cheapest_to_b(a, b, move_count);
	sort_three(a, move_count);
	while (*b)
		pa(a, b, true, move_count);
}

void	ps_push_cheapest_to_b(t_node **a, t_node **b, int *move_count)
{
	int	min_pos;
	int	size;

	size = ps_get_size(*a);
	min_pos = find_min_pos(*a);
	if (min_pos > size / 2)
	{
		while (min_pos++ < size)
			rra(a, true, move_count);
	}
	else
	{
		while (min_pos-- > 0)
			ra(a, true, move_count);
	}
	pb(a, b, true, move_count);
}
