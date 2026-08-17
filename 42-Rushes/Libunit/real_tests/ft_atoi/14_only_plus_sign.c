/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_only_plus_sign.c                                :+:      :+:    :+:   */
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
** Test: "+" --> 0
** Isaret goruldu ama ardindan rakam yok, 0 donmeli.
*/
int	t14_only_plus_sign(void)
{
	if (ft_atoi("+") == atoi("+"))
		return (0);
	return (-1);
}
