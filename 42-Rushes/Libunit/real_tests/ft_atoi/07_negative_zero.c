/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_negative_zero.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 16:30:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_atoi(const char *nptr);

/* Test: "-0" -- negatif sifir, 0 donmeli */
int	t07_negative_zero(void)
{
	if (ft_atoi("-0") == atoi("-0"))
		return (0);
	return (-1);
}
