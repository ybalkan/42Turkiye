/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:15:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:43:54 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

static void	print_str_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

static void	print_num_fd(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		print_num_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static void	print_ops_stats(int *moves)
{
	print_str_fd("\n[bench] Total operations: ", 2);
	print_num_fd(moves[0], 2);
	print_str_fd("\n[bench] sa: ", 2);
	print_num_fd(moves[1], 2);
	print_str_fd(", sb: ", 2);
	print_num_fd(moves[2], 2);
	print_str_fd(", ss: ", 2);
	print_num_fd(moves[3], 2);
	print_str_fd(", pa: ", 2);
	print_num_fd(moves[4], 2);
	print_str_fd(", pb: ", 2);
	print_num_fd(moves[5], 2);
	print_str_fd("\n[bench] ra: ", 2);
	print_num_fd(moves[6], 2);
	print_str_fd(", rb: ", 2);
	print_num_fd(moves[7], 2);
	print_str_fd(", rr: ", 2);
	print_num_fd(moves[8], 2);
	print_str_fd("\n[bench] rra: ", 2);
	print_num_fd(moves[9], 2);
	print_str_fd(", rrb: ", 2);
	print_num_fd(moves[10], 2);
	print_str_fd(", rrr: ", 2);
	print_num_fd(moves[11], 2);
	print_str_fd("\n", 2);
}

void	print_bench_stats(int mistakes, int size, int *moves, char *strategy)
{
	long	total_pairs;
	long	disorder_pct;

	total_pairs = (long)size * (size - 1) / 2;
	if (total_pairs == 0)
		disorder_pct = 0;
	else
		disorder_pct = ((long)mistakes * 10000) / total_pairs;
	print_str_fd("[bench] Disorder: ", 2);
	print_num_fd(disorder_pct / 100, 2);
	print_str_fd(".", 2);
	if (disorder_pct % 100 < 10)
		print_str_fd("0", 2);
	print_num_fd(disorder_pct % 100, 2);
	print_str_fd("%\n[bench] Strategy: ", 2);
	print_str_fd(strategy, 2);
	print_ops_stats(moves);
}
