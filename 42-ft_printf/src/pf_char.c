/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:23:42 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:43 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	pf_char(va_list *args)
{
	unsigned char	c;

	c = (unsigned char)va_arg(*args, int);
	return (ft_putchar(c));
}

int	pf_percent(va_list *args)
{
	(void)args;
	return (ft_putchar('%'));
}
