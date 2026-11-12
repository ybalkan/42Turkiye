/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:30:03 by username          #+#    #+#             */
/*   Updated: 2026/11/07 00:30:08 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	dongle_available(t_dongle *dongle, long long now)
{
	int	available;

	pthread_mutex_lock(&dongle->mutex);
	available = (!dongle->is_in_use && dongle->cooldown_until <= now);
	pthread_mutex_unlock(&dongle->mutex);
	return (available);
}

void	dongle_take(t_dongle *dongle, int coder_id, t_sched_type type)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_in_use = 1;
	heap_remove(&dongle->queue, coder_id, type);
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_release(t_dongle *dongle, long long now, long long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_in_use = 0;
	dongle->cooldown_until = now + cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}
