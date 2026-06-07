/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:31 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:56 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr_base(unsigned long n, char *base)
{
	int				len;
	int				ret;
	unsigned long	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		ret = ft_putnbr_base(n / base_len, base);
		if (ret == -1)
			return (-1);
		len += ret;
		if (ft_putchar(base[n % base_len]) == -1)
			return (-1);
		len++;
	}
	else
	{
		if (ft_putchar(base[n]) == -1)
			return (-1);
		len++;
	}
	return (len);
}
