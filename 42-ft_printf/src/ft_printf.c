/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:14 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:35 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	handle(const char **fmt, va_list *args, t_func *table)
{
	int	ret;

	(*fmt)++;
	if (table[(unsigned char)**fmt])
	{
		ret = table[(unsigned char)**fmt](args);
		if (ret == -1)
			return (-1);
		return (ret);
	}
	if (ft_putchar('%') == -1)
		return (-1);
	if (ft_putchar(**fmt) == -1)
		return (-1);
	return (2);
}

static int	parse(const char *fmt, va_list *args, t_func *table)
{
	int	len;
	int	ret;

	len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			ret = handle(&fmt, args, table);
			if (ret == -1)
				return (-1);
			len += ret;
		}
		else
		{
			if (ft_putchar(*fmt) == -1)
				return (-1);
			len++;
		}
		fmt++;
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	t_func	table[256];
	int		len;

	if (!fmt)
		return (0);
	init_table(table);
	va_start(args, fmt);
	len = parse(fmt, &args, table);
	va_end(args);
	return (len);
}
