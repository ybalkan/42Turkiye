/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:25:23 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/26 08:22:33 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_item
{
	char			*content;
	int				len;
	struct s_item	*next;
}					t_item;

char	*get_next_line(int fd);

int		has_newline(t_item *pending);
void	add_item(t_item **pending, t_item **last, char *content, int len);
void	free_all_items(t_item **pending);
int		count_len(t_item *pending);
t_item	*create_res_item(t_item *temp, int i);

#endif
