/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:48:42 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:24 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef enum e_mode
{
	MODE_SIMPLE,
	MODE_MEDIUM,
	MODE_COMPLEX,
	MODE_ADAPTIVE
}	t_mode;

typedef struct s_sort_params
{
	t_mode	mode;
	bool	bench;
}	t_sort_params;

typedef struct s_node
{
	int				value;
	int				index;
	int				pos;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

t_mode	ps_stack_init(t_node **stack_a, int argc, char **argv);
void	ps_free_all(t_node **stack);
void	ps_error_exit(t_node **stack_a, t_node **stack_b);
void	ps_dispatch_sort(t_node **a, t_node **b, int *moves, t_sort_params *p);
void	print_bench_stats(int mistakes, int size, int *moves, char *strategy);
int		ps_get_disorder(t_node *stack);

t_mode	ps_parse_input(int argc, char **argv, t_node **stack_a);
bool	ps_check_number(char *str);
bool	ps_check_duplicates(t_node *stack, int num);
char	**ps_split(char const *s, char c);
long	ps_atoi(char *str);
int		ps_strcmp(const char *s1, const char *s2);
void	ps_free_args(char **args);

int		ps_get_size(t_node *stack);
bool	ps_is_sorted(t_node *stack);
t_node	*ps_get_last(t_node *stack);
t_node	*ps_node_new(int value);
void	ps_node_add_back(t_node **stack, t_node *new);

#endif
