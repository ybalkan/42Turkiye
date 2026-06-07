/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:01 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:46 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	pf_int(va_list *args)
{
	int	n;

	n = va_arg(*args, int);
	return (ft_putnbr(n));
}

int	pf_unsigned(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (ft_putnbr_base((unsigned long)n, "0123456789"));
}
