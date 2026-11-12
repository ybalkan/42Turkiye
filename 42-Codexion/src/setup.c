/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 22:05:23 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:32:04 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

static int	init_sync(t_sim *sim)
{
	if (pthread_mutex_init(&sim->sched_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&sim->log_mutex, NULL))
	{
		pthread_mutex_destroy(&sim->sched_mutex);
		return (1);
	}
	if (pthread_cond_init(&sim->sched_cond, NULL))
	{
		pthread_mutex_destroy(&sim->log_mutex);
		pthread_mutex_destroy(&sim->sched_mutex);
		return (1);
	}
	return (0);
}

void	destroy_sync(t_sim *sim)
{
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->sched_mutex);
	pthread_cond_destroy(&sim->sched_cond);
}

static int	init_memory(t_sim *sim)
{
	int	n;

	n = sim->rules.num_coders;
	sim->dongles = (t_dongle *)malloc(sizeof(t_dongle) * n);
	if (!sim->dongles)
		return (1);
	sim->coders = (t_coder *)malloc(sizeof(t_coder) * n);
	if (!sim->coders)
	{
		free(sim->dongles);
		sim->dongles = NULL;
		return (1);
	}
	memset(sim->dongles, 0, sizeof(t_dongle) * n);
	memset(sim->coders, 0, sizeof(t_coder) * n);
	return (0);
}

int	init_simulation(t_sim *sim, t_rules *rules)
{
	memset(sim, 0, sizeof(t_sim));
	sim->rules = *rules;
	sim->start_time = get_time_ms();
	if (init_sync(sim))
		return (1);
	if (init_memory(sim))
	{
		destroy_sync(sim);
		return (1);
	}
	if (init_dongles(sim))
	{
		free(sim->dongles);
		free(sim->coders);
		destroy_sync(sim);
		return (1);
	}
	init_coders(sim);
	return (0);
}
