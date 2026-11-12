/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 22:10:24 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:30:03 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	dongle_init(t_dongle *dongle, int id, int capacity)
{
	memset(dongle, 0, sizeof(t_dongle));
	dongle->id = id;
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (1);
	if (heap_init(&dongle->queue, capacity))
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	return (0);
}

void	dongle_destroy(t_dongle *dongle)
{
	heap_destroy(&dongle->queue);
	pthread_mutex_destroy(&dongle->mutex);
}

void	dongle_enqueue(t_dongle *dongle, t_request req, t_sched_type type)
{
	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->queue, req, type);
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_remove(t_dongle *dongle, int coder_id, t_sched_type type)
{
	pthread_mutex_lock(&dongle->mutex);
	heap_remove(&dongle->queue, coder_id, type);
	pthread_mutex_unlock(&dongle->mutex);
}
