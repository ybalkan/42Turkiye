/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 14:00:00 by ybalkan           #+#    #+#             */
/*   Updated: 2026/08/16 20:57:00 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libunit.h"

static int	count_tests(t_unit_test *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

static t_bool	buf_init(t_result_buf *buf, int capacity)
{
	buf->data = (t_result *)malloc(sizeof(t_result) * capacity);
	if (!buf->data)
		return (FALSE);
	buf->count = 0;
	buf->capacity = capacity;
	return (TRUE);
}

static t_status	analyze(int status)
{
	int	sig;

	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (STATUS_OK);
	if (WIFEXITED(status))
		return (STATUS_KO);
	if (!WIFSIGNALED(status))
		return (STATUS_UNKNOWN);
	sig = WTERMSIG(status);
	if (sig == SIGSEGV)
		return (STATUS_SEGV);
	if (sig == SIGBUS)
		return (STATUS_BUS);
	if (sig == SIGABRT)
		return (STATUS_ABRT);
	if (sig == SIGFPE)
		return (STATUS_FPE);
	if (sig == SIGPIPE)
		return (STATUS_PIPE);
	if (sig == SIGILL)
		return (STATUS_ILL);
	return (STATUS_UNKNOWN);
}

static void	run_all(t_unit_test *lst, t_result_buf *buf)
{
	pid_t	pid;
	int		wstatus;
	int		i;

	i = 0;
	while (lst && i < buf->capacity)
	{
		pid = fork();
		if (pid == 0)
			_exit(lst->test());
		if (pid < 0)
			buf->data[i].status = STATUS_UNKNOWN;
		else
		{
			waitpid(pid, &wstatus, 0);
			buf->data[i].status = analyze(wstatus);
		}
		buf->data[i].func_name = lst->func_name;
		buf->data[i].test_name = lst->name;
		i++;
		lst = lst->next;
	}
	buf->count = i;
}

int	launch_tests(t_unit_test **lst)
{
	t_result_buf	buf;
	t_unit_test		*tmp;
	t_bool			all_ok;
	int				total;

	total = count_tests(*lst);
	if (total == 0)
		return (0);
	if (buf_init(&buf, total) == FALSE)
		return (-1);
	run_all(*lst, &buf);
	all_ok = print_all(&buf);
	free(buf.data);
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	if (all_ok == TRUE)
		return (0);
	return (-1);
}
