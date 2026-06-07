/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:25:16 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/02 18:32:05 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_file(int fd, t_item **pending)
{
	char	*buffer;
	int		read_bytes;
	t_item	*last;

	last = *pending;
	while (last && last->next)
		last = last->next;
	while (!has_newline(last))
	{
		buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buffer);
			if (read_bytes < 0)
				free_all_items(pending);
			return ;
		}
		buffer[read_bytes] = '\0';
		add_item(pending, &last, buffer, read_bytes);
	}
}

char	*create_line(t_item *pending)
{
	int		i;
	int		j;
	char	*line;

	line = malloc(sizeof(char) * (count_len(pending) + 1));
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

static void	clear_help(t_item **pending, t_item *temp, t_item *new_p)
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

void	clear_item(t_item **pending)
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
				new_pending = create_res_item(temp, i + 1);
				clear_help(pending, temp, new_pending);
				return ;
			}
			i++;
		}
		temp = temp->next;
	}
	free_all_items(pending);
}

char	*get_next_line(int fd)
{
	static t_item	*pending = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_all_items(&pending);
		return (NULL);
	}
	read_file(fd, &pending);
	if (!pending)
		return (NULL);
	line = create_line(pending);
	clear_item(&pending);
	return (line);
}
