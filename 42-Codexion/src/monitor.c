/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 22:40:12 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:31:46 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

#define BURNOUT_SLACK 4
#define SPIN_MARGIN 12

static t_coder	*find_burnout(t_sim *sim, long long now)
{
	t_coder	*coder;
	int		i;

	i = 0;
	while (i < sim->rules.num_coders)
	{
		coder = &sim->coders[i];
		if (coder->compile_count < sim->rules.compiles_required
			&& now >= coder->last_compile_start + sim->rules.time_to_burnout
			+ BURNOUT_SLACK)
			return (coder);
		i++;
	}
	return (NULL);
}

static long long	next_deadline(t_sim *sim)
{
	long long	deadline;
	long long	current;
	int			i;

	deadline = -1;
	i = 0;
	while (i < sim->rules.num_coders)
	{
		if (sim->coders[i].compile_count < sim->rules.compiles_required)
		{
			current = sim->coders[i].last_compile_start
				+ sim->rules.time_to_burnout + BURNOUT_SLACK;
			if (deadline < 0 || current < deadline)
				deadline = current;
		}
		i++;
	}
	return (deadline);
}

static void	wait_monitor(t_sim *sim, long long deadline)
{
	struct timespec	ts;
	long long		now;

	now = get_time_ms();
	if (deadline < 0 || deadline > now + 50)
		deadline = now + 50;
	if (deadline - now <= SPIN_MARGIN)
	{
		pthread_mutex_unlock(&sim->sched_mutex);
		while (get_time_ms() < deadline)
			;
		pthread_mutex_lock(&sim->sched_mutex);
		return ;
	}
	ms_to_timespec(deadline - SPIN_MARGIN, &ts);
	pthread_cond_timedwait(&sim->sched_cond, &sim->sched_mutex, &ts);
}

static void	stop_with_burnout(t_sim *sim, t_coder *victim, long long now)
{
	sim->simulation_ended = 1;
	pthread_cond_broadcast(&sim->sched_cond);
	pthread_mutex_unlock(&sim->sched_mutex);
	log_line(sim, victim->id, "burned out", now);
}

void	*monitor_routine(void *arg)
{
	t_sim		*sim;
	t_coder		*victim;
	long long	now;

	sim = (t_sim *)arg;
	pthread_mutex_lock(&sim->sched_mutex);
	while (!sim->simulation_ended)
	{
		if (all_compiled(sim))
		{
			sim->simulation_ended = 1;
			pthread_cond_broadcast(&sim->sched_cond);
			break ;
		}
		now = get_time_ms();
		victim = find_burnout(sim, now);
		if (victim)
		{
			stop_with_burnout(sim, victim, now);
			return (NULL);
		}
		wait_monitor(sim, next_deadline(sim));
	}
	pthread_mutex_unlock(&sim->sched_mutex);
	return (NULL);
}
