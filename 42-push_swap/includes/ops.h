/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:38:10 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/17 17:39:21 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "ps.h"

void	sa(t_node **stack_a, bool print, int *move_count);

void	pa(t_node **stack_a, t_node **stack_b, bool print, int *move_count);
void	pb(t_node **stack_a, t_node **stack_b, bool print, int *move_count);

void	ra(t_node **stack_a, bool print, int *move_count);
void	rb(t_node **stack_b, bool print, int *move_count);

void	rra(t_node **stack_a, bool print, int *move_count);
void	rrb(t_node **stack_b, bool print, int *move_count);

#endif
