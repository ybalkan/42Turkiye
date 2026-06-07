/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:49:04 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:36:05 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"
#include "algo.h"
#include "ops.h"

static void	ps_parse_flags(int *argc, char ***argv, t_sort_params *p)
{
	while (*argc > 1 && (*argv)[1][0] == '-')
	{
		if (ps_strcmp((*argv)[1], "--bench") == 0)
			p->bench = true;
		else if (ps_strcmp((*argv)[1], "--simple") == 0)
			p->mode = MODE_SIMPLE;
		else if (ps_strcmp((*argv)[1], "--medium") == 0)
			p->mode = MODE_MEDIUM;
		else if (ps_strcmp((*argv)[1], "--complex") == 0)
			p->mode = MODE_COMPLEX;
		else if (ps_strcmp((*argv)[1], "--adaptive") == 0)
			p->mode = MODE_ADAPTIVE;
		else
			break ;
		(*argc)--;
		(*argv)++;
	}
}

int	main(int argc, char **argv)
{
	t_node			*a;
	t_node			*b;
	t_sort_params	p;
	int				move_count[12];
	int				i;

	a = NULL;
	b = NULL;
	p.bench = false;
	p.mode = MODE_ADAPTIVE;
	i = 0;
	while (i < 12)
		move_count[i++] = 0;
	if (argc < 2)
		return (0);
	ps_parse_flags(&argc, &argv, &p);
	ps_stack_init(&a, argc, argv);
	if (!a || ps_is_sorted(a))
	{
		ps_free_all(&a);
		return (0);
	}
	ps_dispatch_sort(&a, &b, move_count, &p);
	ps_free_all(&a);
	return (0);
}
