/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 22:10:24 by username          #+#    #+#             */
/*   Updated: 2026/11/07 00:29:43 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

static void	enqueue_request(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	coder->request.coder_id = coder->id;
	coder->request.seq = ++sim->seq_counter;
	coder->request.deadline = coder->last_compile_start
		+ sim->rules.time_to_burnout;
	dongle_enqueue(coder->first, coder->request, sim->rules.scheduler);
	dongle_enqueue(coder->second, coder->request, sim->rules.scheduler);
	coder->waiting = 1;
}

static void	remove_request(t_coder *coder)
{
	coder->waiting = 0;
	dongle_remove(coder->first, coder->id, coder->sim->rules.scheduler);
	dongle_remove(coder->second, coder->id, coder->sim->rules.scheduler);
}

static void	wait_grant(t_sim *sim)
{
	struct timespec	ts;

	ms_to_timespec(get_time_ms() + 1, &ts);
	pthread_cond_timedwait(&sim->sched_cond, &sim->sched_mutex, &ts);
}

static int	wait_for_turn(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	enqueue_request(coder);
	while (!sim->simulation_ended && !coder->granted)
	{
		arbitrate(sim);
		if (!sim->simulation_ended && !coder->granted)
			wait_grant(sim);
	}
	if (!coder->granted)
	{
		remove_request(coder);
		return (0);
	}
	coder->granted = 0;
	return (1);
}

int	acquire_pair(t_coder *coder)
{
	int	acquired;

	pthread_mutex_lock(&coder->sim->sched_mutex);
	if (coder->sim->simulation_ended)
		acquired = 0;
	else
		acquired = wait_for_turn(coder);
	pthread_mutex_unlock(&coder->sim->sched_mutex);
	return (acquired);
}
