/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:31:50 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"
#include <limits.h>

static int	fill_counts(char **argv, t_rules *rules)
{
	long long	value;

	if (parse_number(argv[1], &value) || value < 1 || value > INT_MAX)
		return (print_error("Error: invalid number_of_coders\n"));
	rules->num_coders = (int)value;
	if (parse_number(argv[6], &value) || value < 1 || value > INT_MAX)
		return (print_error("Error: invalid number_of_compiles_required\n"));
	rules->compiles_required = (int)value;
	return (0);
}

static int	fill_times(char **argv, t_rules *rules)
{
	if (parse_number(argv[2], &rules->time_to_burnout))
		return (print_error("Error: invalid time_to_burnout\n"));
	if (parse_number(argv[3], &rules->time_to_compile))
		return (print_error("Error: invalid time_to_compile\n"));
	if (parse_number(argv[4], &rules->time_to_debug))
		return (print_error("Error: invalid time_to_debug\n"));
	if (parse_number(argv[5], &rules->time_to_refactor))
		return (print_error("Error: invalid time_to_refactor\n"));
	if (parse_number(argv[7], &rules->dongle_cooldown))
		return (print_error("Error: invalid dongle_cooldown\n"));
	return (0);
}

int	parse_values(char **argv, t_rules *rules)
{
	if (fill_counts(argv, rules))
		return (1);
	if (fill_times(argv, rules))
		return (1);
	return (0);
}
