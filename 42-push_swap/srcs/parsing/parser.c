/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:39:33 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:40:03 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

static void	ps_validate_fill(t_node **stack_a, char **args, int argc)
{
	int		i;
	long	num;

	i = 0;
	while (args[i])
	{
		if (!ps_check_number(args[i]))
		{
			if (argc == 2)
				ps_free_args(args);
			ps_error_exit(stack_a, NULL);
		}
		num = ps_atoi(args[i]);
		if (num > INT_MAX || num < INT_MIN
			|| ps_check_duplicates(*stack_a, (int)num))
		{
			if (argc == 2)
				ps_free_args(args);
			ps_error_exit(stack_a, NULL);
		}
		ps_node_add_back(stack_a, ps_node_new((int)num));
		i++;
	}
}

t_mode	ps_parse_input(int argc, char **argv, t_node **stack_a)
{
	char	**args;
	t_mode	mode;
	int		off;

	mode = MODE_ADAPTIVE;
	off = 1;
	if (argc == off + 1)
		args = ps_split(argv[off], ' ');
	else
		args = argv + off;
	if (!args || !args[0])
		return (mode);
	ps_validate_fill(stack_a, args, argc);
	if (argc == off + 1)
		ps_free_args(args);
	return (mode);
}
