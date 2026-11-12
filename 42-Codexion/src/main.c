/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:22:47 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:31:36 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	main(int argc, char **argv)
{
	t_sim	sim;
	t_rules	rules;

	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_simulation(&sim, &rules))
		return (print_error("Error: initialization failed\n"));
	if (start_threads(&sim))
	{
		join_threads(&sim);
		cleanup_simulation(&sim);
		return (1);
	}
	join_threads(&sim);
	cleanup_simulation(&sim);
	return (0);
}
