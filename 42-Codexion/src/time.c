/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 22:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:23:20 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ms_to_timespec(long long ms, struct timespec *ts)
{
	ts->tv_sec = (time_t)(ms / 1000);
	ts->tv_nsec = (long)((ms % 1000) * 1000000);
}

void	precise_sleep(long long duration, t_sim *sim)
{
	long long	target;
	long long	now;
	long long	chunk;

	target = get_time_ms() + duration;
	while (!is_simulation_ended(sim))
	{
		now = get_time_ms();
		if (now >= target)
			break ;
		chunk = target - now;
		if (chunk > 2)
			chunk = 2;
		usleep((useconds_t)(chunk * 1000));
	}
}

int	is_simulation_ended(t_sim *sim)
{
	int	ended;

	pthread_mutex_lock(&sim->sched_mutex);
	ended = sim->simulation_ended;
	pthread_mutex_unlock(&sim->sched_mutex);
	return (ended);
}
