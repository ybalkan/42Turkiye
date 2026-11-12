/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 22:02:20 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:31:56 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

static int	is_eligible(t_coder *coder, long long now)
{
	if (!coder->waiting)
		return (0);
	if (!dongle_available(coder->first, now))
		return (0);
	if (!dongle_available(coder->second, now))
		return (0);
	return (1);
}

static t_coder	*find_coder(t_sim *sim, long long now, int only_eligible)
{
	t_coder	*best;
	int		i;

	best = NULL;
	i = 0;
	while (i < sim->rules.num_coders)
	{
		if (sim->coders[i].waiting
			&& (!only_eligible || is_eligible(&sim->coders[i], now)))
		{
			if (!best || compare_requests(&sim->coders[i].request,
					&best->request, sim->rules.scheduler))
				best = &sim->coders[i];
		}
		i++;
	}
	return (best);
}

int	all_compiled(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->rules.num_coders)
	{
		if (sim->coders[i].compile_count < sim->rules.compiles_required)
			return (0);
		i++;
	}
	return (1);
}

static void	grant_pair(t_sim *sim, t_coder *coder, long long now)
{
	dongle_take(coder->first, coder->id, sim->rules.scheduler);
	dongle_take(coder->second, coder->id, sim->rules.scheduler);
	coder->waiting = 0;
	coder->granted = 1;
	coder->last_compile_start = now;
	coder->compile_count++;
	log_compile_start(sim, coder, now);
	if (all_compiled(sim))
		sim->simulation_ended = 1;
}

void	arbitrate(t_sim *sim)
{
	t_coder		*best;
	long long	now;

	if (sim->simulation_ended)
		return ;
	now = get_time_ms();
	best = find_coder(sim, now, 0);
	if (best && is_eligible(best, now))
	{
		grant_pair(sim, best, now);
		best = find_coder(sim, now, 1);
		while (best && !sim->simulation_ended)
		{
			grant_pair(sim, best, now);
			best = find_coder(sim, now, 1);
		}
	}
	pthread_cond_broadcast(&sim->sched_cond);
}
