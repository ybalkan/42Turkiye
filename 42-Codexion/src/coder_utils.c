/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 22:14:54 by username          #+#    #+#             */
/*   Updated: 2026/11/07 00:29:56 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	reached_required(t_coder *coder)
{
	int	reached;

	pthread_mutex_lock(&coder->sim->sched_mutex);
	reached = coder->compile_count >= coder->sim->rules.compiles_required;
	pthread_mutex_unlock(&coder->sim->sched_mutex);
	return (reached);
}
