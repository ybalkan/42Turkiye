/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:25:16 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/02 18:33:33 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_file_bonus(int fd, t_item **pending)
{
	char	*buffer;
	int		read_bytes;
	t_item	*last;

	last = *pending;
	while (last && last->next)
		last = last->next;
	while (!has_newline_bonus(last))
	{
		buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buffer);
			if (read_bytes < 0)
				free_all_items_bonus(pending);
			return ;
		}
		buffer[read_bytes] = '\0';
		add_item_bonus(pending, &last, buffer, read_bytes);
	}
}

char	*create_line_bonus(t_item *pending)
{
	int		i;
	int		j;
	char	*line;

	line = malloc(sizeof(char) * (count_len_bonus(pending) + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (pending)
	{
		i = 0;
		while (i < pending->len)
		{
			line[j++] = pending->content[i];
			if (pending->content[i++] == '\n')
			{
				line[j] = '\0';
				return (line);
			}
		}
		pending = pending->next;
	}
	line[j] = '\0';
	return (line);
}

static void	clear_help_bonus(t_item **pending, t_item *temp, t_item *new_p)
{
	t_item	*next_node;

	while (*pending)
	{
		next_node = (*pending)->next;
		if (*pending == temp)
		{
			free((*pending)->content);
			free(*pending);
			*pending = new_p;
			return ;
		}
		free((*pending)->content);
		free(*pending);
		*pending = next_node;
	}
}

void	clear_item_bonus(t_item **pending)
{
	t_item	*temp;
	t_item	*new_pending;
	int		i;

	temp = *pending;
	while (temp)
	{
		i = 0;
		while (i < temp->len)
		{
			if (temp->content[i] == '\n')
			{
				new_pending = create_res_item_bonus(temp, i + 1);
				clear_help_bonus(pending, temp, new_pending);
				return ;
			}
			i++;
		}
		temp = temp->next;
	}
	free_all_items_bonus(pending);
}

char	*get_next_line(int fd)
{
	static t_item	*pending[FD_SETSIZE];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SETSIZE)
	{
		if (fd >= 0 && fd < FD_SETSIZE)
			free_all_items_bonus(&pending[fd]);
		return (NULL);
	}
	read_file_bonus(fd, &pending[fd]);
	if (!pending[fd])
		return (NULL);
	line = create_line_bonus(pending[fd]);
	clear_item_bonus(&pending[fd]);
	return (line);
}
