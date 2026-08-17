/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 15:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 20:57:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../framework/bonus/libunit_bonus.h"
#else
# include "../framework/mandatory/libunit.h"
#endif

int	ft_atoi_launcher(void);

int	main(void)
{
	return (ft_atoi_launcher());
}
