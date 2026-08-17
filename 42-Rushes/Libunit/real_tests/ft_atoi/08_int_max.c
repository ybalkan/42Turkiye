/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_int_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 16:30:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

int	ft_atoi(const char *nptr);

/* Test: "2147483647" == INT_MAX -- int araliginin pozitif siniri */
int	t08_int_max(void)
{
	if (ft_atoi("2147483647") == INT_MAX)
		return (0);
	return (-1);
}
