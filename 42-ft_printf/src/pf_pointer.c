/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:05 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/18 15:51:51 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	pf_pointer(va_list *args)
{
	unsigned long	ptr;
	int				len;
	int				ret;

	ptr = va_arg(*args, unsigned long);
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x");
	if (len == -1)
		return (-1);
	ret = ft_putnbr_base(ptr, "0123456789abcdef");
	if (ret == -1)
		return (-1);
	return (len + ret);
}
