/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 02:50:22 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:52:01 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	len;
	int	ret;

	if (!s)
		return (ft_putstr("(null)"));
	len = 0;
	while (*s)
	{
		ret = ft_putchar(*s++);
		if (ret == -1)
			return (-1);
		len += ret;
	}
	return (len);
}

static int	ft_handle_sign(long *nb, int *len)
{
	if (*nb < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		(*len)++;
		*nb = -(*nb);
	}
	return (0);
}

int	ft_putnbr(int n)
{
	int		len;
	int		ret;
	long	nb;

	len = 0;
	nb = n;
	if (ft_handle_sign(&nb, &len) == -1)
		return (-1);
	if (nb >= 10)
	{
		ret = ft_putnbr(nb / 10);
		if (ret == -1)
			return (-1);
		len += ret;
		if (ft_putchar((nb % 10) + '0') == -1)
			return (-1);
		len++;
	}
	else
	{
		if (ft_putchar(nb + '0') == -1)
			return (-1);
		len++;
	}
	return (len);
}
