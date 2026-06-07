/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:00:23 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 13:59:52 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "algo.h"
#include "ops.h"

static char	*execute_simple(t_node **a, t_node **b, int *moves, int size)
{
	if (size == 2)
		sa(a, true, moves);
	else if (size == 3)
		sort_three(a, moves);
	else if (size > 1)
		ps_sort_small(a, b, moves);
	return ("Simple O(n^2)");
}

static char	*get_strategy(t_node **a, t_node **b, int *moves,
			long *stats)
{
	int		size;
	char	*strategy;
	t_mode	mode;

	size = ps_get_size(*a);
	mode = (t_mode)stats[2];
	if (mode == MODE_SIMPLE || (mode == MODE_ADAPTIVE
			&& (size <= 5 || (stats[0] > 0 && stats[1] < stats[0] / 5))))
		strategy = execute_simple(a, b, moves, size);
	else
	{
		strategy = "Adaptive O(n log n) engine";
		if (mode == MODE_COMPLEX)
			strategy = "Complex O(n log n)";
		else if (mode == MODE_MEDIUM)
			strategy = "Medium O(n^1.5)";
		ps_sort_engine(a, b, moves);
	}
	return (strategy);
}

void	ps_dispatch_sort(t_node **a, t_node **b, int *moves, t_sort_params *p)
{
	long	pairs_and_mistakes[3];
	char	*strategy;
	int		size;

	size = ps_get_size(*a);
	pairs_and_mistakes[1] = ps_get_disorder(*a);
	pairs_and_mistakes[0] = (long)size * (size - 1) / 2;
	pairs_and_mistakes[2] = p->mode;
	strategy = get_strategy(a, b, moves, pairs_and_mistakes);
	if (p->bench)
		print_bench_stats(pairs_and_mistakes[1], size, moves, strategy);
}
