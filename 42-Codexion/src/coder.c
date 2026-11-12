/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 22:10:24 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:30:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->sim->rules.num_coders == 1)
	{
		wait_single(coder);
		return (NULL);
	}
	while (!is_simulation_ended(coder->sim))
	{
		if (!acquire_pair(coder))
			break ;
		precise_sleep(coder->sim->rules.time_to_compile, coder->sim);
		release_pair(coder);
		if (is_simulation_ended(coder->sim))
			break ;
		precise_sleep(coder->sim->rules.time_to_debug, coder->sim);
		mark_refactoring(coder);
		if (is_simulation_ended(coder->sim))
			break ;
		precise_sleep(coder->sim->rules.time_to_refactor, coder->sim);
		if (reached_required(coder))
			break ;
	}
	return (NULL);
}

void	release_pair(t_coder *coder)
{
	t_sim		*sim;
	long long	now;

	sim = coder->sim;
	pthread_mutex_lock(&sim->sched_mutex);
	now = get_time_ms();
	dongle_release(coder->first, now, sim->rules.dongle_cooldown);
	dongle_release(coder->second, now, sim->rules.dongle_cooldown);
	if (!sim->simulation_ended)
		log_line(sim, coder->id, "is debugging", now);
	arbitrate(sim);
	pthread_cond_broadcast(&sim->sched_cond);
	pthread_mutex_unlock(&sim->sched_mutex);
}

void	mark_refactoring(t_coder *coder)
{
	t_sim		*sim;
	long long	now;

	sim = coder->sim;
	pthread_mutex_lock(&sim->sched_mutex);
	now = get_time_ms();
	if (!sim->simulation_ended)
		log_line(sim, coder->id, "is refactoring", now);
	pthread_mutex_unlock(&sim->sched_mutex);
}

void	wait_single(t_coder *coder)
{
	t_sim			*sim;
	struct timespec	ts;

	sim = coder->sim;
	pthread_mutex_lock(&sim->sched_mutex);
	while (!sim->simulation_ended)
	{
		ms_to_timespec(get_time_ms() + 20, &ts);
		pthread_cond_timedwait(&sim->sched_cond, &sim->sched_mutex, &ts);
	}
	pthread_mutex_unlock(&sim->sched_mutex);
}
