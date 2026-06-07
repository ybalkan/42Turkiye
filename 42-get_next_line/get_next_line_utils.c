/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:25:07 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/02 18:33:17 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(t_item *pending)
{
	int	i;

	while (pending)
	{
		i = 0;
		while (i < pending->len)
		{
			if (pending->content[i] == '\n')
				return (1);
			i++;
		}
		pending = pending->next;
	}
	return (0);
}

void	add_item(t_item **pending, t_item **last, char *content, int len)
{
	t_item	*new_node;

	new_node = malloc(sizeof(t_item));
	if (!new_node)
	{
		free(content);
		return ;
	}
	new_node->content = content;
	new_node->len = len;
	new_node->next = NULL;
	if (!*pending)
		*pending = new_node;
	if (*last)
		(*last)->next = new_node;
	*last = new_node;
}

void	free_all_items(t_item **pending)
{
	t_item	*next_node;

	while (*pending)
	{
		next_node = (*pending)->next;
		free((*pending)->content);
		free(*pending);
		*pending = next_node;
	}
}

int	count_len(t_item *pending)
{
	int	len;
	int	i;

	len = 0;
	while (pending)
	{
		i = 0;
		while (i < pending->len)
		{
			len++;
			if (pending->content[i] == '\n')
				return (len);
			i++;
		}
		pending = pending->next;
	}
	return (len);
}

t_item	*create_res_item(t_item *temp, int i)
{
	t_item	*new_pending;
	char	*res;
	int		j;

	new_pending = NULL;
	if (i < temp->len)
	{
		res = malloc(sizeof(char) * (temp->len - i + 1));
		if (!res)
			return (NULL);
		j = 0;
		while (i < temp->len)
			res[j++] = temp->content[i++];
		res[j] = '\0';
		new_pending = malloc(sizeof(t_item));
		if (!new_pending)
		{
			free(res);
			return (NULL);
		}
		new_pending->content = res;
		new_pending->len = j;
		new_pending->next = NULL;
	}
	return (new_pending);
}
