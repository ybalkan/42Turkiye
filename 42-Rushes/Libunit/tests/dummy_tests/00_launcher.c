/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:10:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/17 19:54:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "../../framework/mandatory/libunit.h"
#else
# include "../../framework/bonus/libunit_bonus.h"
#endif

int	ok_test(void);
int	ko_test(void);
int	segv_test(void);
int	bus_test(void);
int	abrt_test(void);
int	fpe_test(void);
int	pipe_test(void);
int	ill_test(void);
int	timeout_test(void);

static void	load_dummy_tests(t_unit_test **lst)
{
	load_test(lst, "DUMMY", "OK test", &ok_test);
	load_test(lst, "DUMMY", "KO test", &ko_test);
	load_test(lst, "DUMMY", "SIGSEGV test", &segv_test);
	load_test(lst, "DUMMY", "SIGBUS test", &bus_test);
	load_test(lst, "DUMMY", "SIGABRT test", &abrt_test);
	load_test(lst, "DUMMY", "SIGFPE test", &fpe_test);
	load_test(lst, "DUMMY", "SIGPIPE test", &pipe_test);
	load_test(lst, "DUMMY", "SIGILL test", &ill_test);
}

#ifdef BONUS

static void	load_bonus_tests(t_unit_test **lst)
{
	load_test(lst, "BONUS", "TIMEOUT test", &timeout_test);
}

#else

static void	load_bonus_tests(t_unit_test **lst)
{
	(void)lst;
}

#endif

int	dummy_tests_launcher(void)
{
	t_unit_test	*testlist;

	testlist = NULL;
	load_dummy_tests(&testlist);
	load_bonus_tests(&testlist);
	return (launch_tests(&testlist));
}
