/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:23:53 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:49 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	pf_hex_lower(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (ft_putnbr_base((unsigned long)n, "0123456789abcdef"));
}

int	pf_hex_upper(va_list *args)
{
	unsigned int	n;

	n = va_arg(*args, unsigned int);
	return (ft_putnbr_base((unsigned long)n, "0123456789ABCDEF"));
}
