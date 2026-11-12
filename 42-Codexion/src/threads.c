/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 20:12:23 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:32:15 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

static void	stop_started(t_sim *sim)
{
	pthread_mutex_lock(&sim->sched_mutex);
	sim->simulation_ended = 1;
	pthread_cond_broadcast(&sim->sched_cond);
	pthread_mutex_unlock(&sim->sched_mutex);
}

int	start_threads(t_sim *sim)
{
	int	i;

	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim))
		return (1);
	sim->monitor_started = 1;
	i = 0;
	while (i < sim->rules.num_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]))
		{
			stop_started(sim);
			return (1);
		}
		sim->started_coders++;
		i++;
	}
	return (0);
}

void	join_threads(t_sim *sim)
{
	int	i;

	if (sim->monitor_started)
		pthread_join(sim->monitor, NULL);
	i = 0;
	while (i < sim->started_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}
