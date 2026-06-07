/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:26 by ybalkan           #+#    #+#             */
/*   Updated: 2026/02/15 00:09:27 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_printf(const char *fmt, ...);

typedef int	(*t_func)(va_list *);

int			pf_char(va_list *args);
int			pf_string(va_list *args);
int			pf_pointer(va_list *args);
int			pf_int(va_list *args);
int			pf_unsigned(va_list *args);
int			pf_hex_lower(va_list *args);
int			pf_hex_upper(va_list *args);
int			pf_percent(va_list *args);

void		init_table(t_func *table);

size_t		ft_strlen(const char *s);
int			ft_putchar(char c);
int			ft_putstr(char *s);
int			ft_putnbr_base(unsigned long n, char *base);
int			ft_putnbr(int n);

#endif
