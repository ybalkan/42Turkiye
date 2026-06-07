/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:48:31 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:13 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "ps.h"

void	ps_sort_small(t_node **stack_a, t_node **stack_b, int *move_count);
void	sort_three(t_node **stack_a, int *move_count);
void	ps_sort_engine(t_node **stack_a, t_node **stack_b, int *move_count);

void	ps_set_rank_indices(t_node *stack);
void	ps_push_cheapest_to_b(t_node **a, t_node **b, int *move_count);
int		find_max_val(t_node *stack);
int		find_min_pos(t_node *stack);
int		find_max_pos(t_node **stack);

#endif
