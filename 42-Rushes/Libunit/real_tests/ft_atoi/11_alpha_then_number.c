/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_alpha_then_number.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 16:30:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

/*
** Test: "abc42" --> 0
** Ilk karakter ne bosluk ne isaret ne de rakam, 0 donmeli.
*/
int	t11_alpha_then_number(void)
{
	if (ft_atoi("abc42") == atoi("abc42"))
		return (0);
	return (-1);
}
