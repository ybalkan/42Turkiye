/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/19 21:44:19 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	init_table(t_func *table)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		table[i] = 0;
		i++;
	}
	table['c'] = &pf_char;
	table['s'] = &pf_string;
	table['p'] = &pf_pointer;
	table['d'] = &pf_int;
	table['i'] = &pf_int;
	table['u'] = &pf_unsigned;
	table['x'] = &pf_hex_lower;
	table['X'] = &pf_hex_upper;
	table['%'] = &pf_percent;
}
