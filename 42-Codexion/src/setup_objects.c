/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 22:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:23:09 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	init_dongles(t_sim *sim)
{
	int	i;
	int	n;

	n = sim->rules.num_coders;
	i = 0;
	while (i < n)
	{
		if (dongle_init(&sim->dongles[i], i, n))
		{
			while (i > 0)
				dongle_destroy(&sim->dongles[--i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_coders(t_sim *sim)
{
	int			i;
	int			n;
	t_coder		*coder;
	t_dongle	*a;
	t_dongle	*b;

	n = sim->rules.num_coders;
	i = 0;
	while (i < n)
	{
		coder = &sim->coders[i];
		a = &sim->dongles[i];
		b = &sim->dongles[(i + n - 1) % n];
		coder->id = i + 1;
		coder->sim = sim;
		coder->first = a;
		coder->second = b;
		if (a->id > b->id)
		{
			coder->first = b;
			coder->second = a;
		}
		coder->last_compile_start = sim->start_time;
		i++;
	}
}

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	if (sim->dongles)
	{
		i = 0;
		while (i < sim->rules.num_coders)
		{
			dongle_destroy(&sim->dongles[i]);
			i++;
		}
	}
	free(sim->dongles);
	free(sim->coders);
	destroy_sync(sim);
}
