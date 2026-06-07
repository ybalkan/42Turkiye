/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:25:23 by ybalkan           #+#    #+#             */
/*   Updated: 2026/03/02 18:33:27 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_SETSIZE
#  define FD_SETSIZE 4096
# endif

typedef struct s_item
{
	char			*content;
	int				len;
	struct s_item	*next;
}					t_item;

char	*get_next_line(int fd);

int		has_newline_bonus(t_item *pending);
void	add_item_bonus(t_item **pending, t_item **last, char *content, int len);
void	free_all_items_bonus(t_item **pending);
int		count_len_bonus(t_item *pending);
t_item	*create_res_item_bonus(t_item *temp, int i);

#endif
