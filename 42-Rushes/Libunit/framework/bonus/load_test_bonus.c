/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 20:57:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libunit_bonus.h"

void	load_test(t_unit_test **lst, char *f_name, char *t_name, int (*t)(void))
{
	t_unit_test	*node;
	t_unit_test	*tail;

	node = (t_unit_test *)malloc(sizeof(t_unit_test));
	if (!node)
		return ;
	node->func_name = f_name;
	node->name = t_name;
	node->test = t;
	node->next = NULL;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tail = *lst;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}
