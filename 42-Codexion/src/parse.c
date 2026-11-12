/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 22:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:23:01 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"
#include <limits.h>

int	print_error(const char *msg)
{
	write(2, msg, strlen(msg));
	return (1);
}

static int	all_digits(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_number(const char *str, long long *out)
{
	long long	value;
	int			i;

	if (!all_digits(str))
		return (1);
	value = 0;
	i = 0;
	while (str[i])
	{
		if (value > (LLONG_MAX - (str[i] - '0')) / 10)
			return (1);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	*out = value;
	return (0);
}

static int	parse_scheduler(const char *str, t_sched_type *scheduler)
{
	if (strcmp(str, "fifo") == 0)
	{
		*scheduler = CODEX_FIFO;
		return (0);
	}
	if (strcmp(str, "edf") == 0)
	{
		*scheduler = CODEX_EDF;
		return (0);
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc != 9)
		return (print_error("Usage: ./codexion coders burnout compile debug "
				"refactor compiles cooldown fifo|edf\n"));
	memset(rules, 0, sizeof(t_rules));
	if (parse_values(argv, rules))
		return (1);
	if (parse_scheduler(argv[8], &rules->scheduler))
		return (print_error("Error: scheduler must be fifo or edf\n"));
	return (0);
}
