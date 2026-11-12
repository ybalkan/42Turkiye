/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:22:47 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:30:36 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

static void	put_number(char *buf, int *len, long long number)
{
	char	digits[24];
	int		i;

	i = 0;
	if (number == 0)
		digits[i++] = '0';
	while (number > 0)
	{
		digits[i++] = (char)('0' + number % 10);
		number /= 10;
	}
	while (i > 0)
		buf[(*len)++] = digits[--i];
}

static void	append_text(char *buf, int *len, const char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		buf[(*len)++] = text[i];
		i++;
	}
}

static void	emit_line(t_sim *sim, int id, const char *msg, long long ts)
{
	char	buf[128];
	int		len;

	len = 0;
	put_number(buf, &len, ts - sim->start_time);
	append_text(buf, &len, " ");
	put_number(buf, &len, id);
	append_text(buf, &len, " ");
	append_text(buf, &len, msg);
	append_text(buf, &len, "\n");
	write(1, buf, len);
}

void	log_line(t_sim *sim, int id, const char *msg, long long ts)
{
	pthread_mutex_lock(&sim->log_mutex);
	emit_line(sim, id, msg, ts);
	pthread_mutex_unlock(&sim->log_mutex);
}

void	log_compile_start(t_sim *sim, t_coder *coder, long long ts)
{
	pthread_mutex_lock(&sim->log_mutex);
	emit_line(sim, coder->id, "has taken a dongle", ts);
	emit_line(sim, coder->id, "has taken a dongle", ts);
	emit_line(sim, coder->id, "is compiling", ts);
	pthread_mutex_unlock(&sim->log_mutex);
}
