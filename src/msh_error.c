/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/16 23:46:52 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static char		*check_funcnum(int funcnum)
{
	if (funcnum == ENV_ERR)
		return ("env");
	else if (funcnum == SENV_ERR)
		return ("setenv");
	else if (funcnum == CD_ERR)
		return ("cd");
	else if (funcnum == EXI_ERR)
		return ("exit");
	else
		return ("minishell");
}

static void		exit_signal(void)
{
	int		ret;
	char	*from;

	from = save_cmdline(NULL, CHECK);
	ret = exit_value(-1, (CHECK | SIGEXIT));
	if (ret == SIGQUIT)
		ft_dprintf(2, "%d quit\t%s\n", last_pid(0), from);
	else if (ret == SIGILL)
		ft_dprintf(2, "%d illegal instruction\t%s\n", last_pid(0), from);
	else if (ret == SIGKILL)
		ft_dprintf(2, "%d killed\t%s\n", last_pid(0), from);
	else if (ret == SIGHUP)
		ft_dprintf(2, "%d hang up\t%s\n", last_pid(0), from);
	else if (ret == SIGTRAP)
		ft_dprintf(2, "%d trace trap\t%s\n", last_pid(0), from);
	else if (ret == SIGABRT)
		ft_dprintf(2, "%d abort\t%s\n", last_pid(0), from);
	else if (ret == SIGEMT)
		ft_dprintf(2, "%d emulate instruction executed\t%s\n", \
		last_pid(0), from);
	else if (ret == SIGFPE)
		ft_dprintf(2, "%d floating-point exception\t%s\n", last_pid(0), from);
	else if (ret == SIGBUS)
		ft_dprintf(2, "%d bus error\t%s\n", last_pid(0), from);
	else if (ret == SIGSEGV)
		ft_dprintf(2, "%d segmentation fault\t%s\n", last_pid(0), from);
	else if (ret == SIGSYS)
		ft_dprintf(2, "%d non-existent system call invoked\t%s\n", \
		last_pid(0), from);
}

void			msh_error(int nbr, char *from, int funcnum)
{
	char	*err;

	err = check_funcnum(funcnum);
	if (from && nbr)
	{
		if (nbr == NO_FILE)
			ft_dprintf(2, "%s: no such file or directory: %s\n", err, from);
		else if (nbr == TM_ARGS)
			ft_dprintf(2, "%s: too many arguments\n", from);
		else if (nbr == NO_CMD)
			ft_dprintf(2, "%s: command not found: %s\n", err, from);
		else if (nbr == STX_ERR)
			ft_dprintf(2, "%s: %s: syntax error\n", err, from);
		else if (nbr == VAR_NSET)
			ft_dprintf(2, "%s: %s not set\n", err, from);
		else if (nbr == PERM_DEN)
			ft_dprintf(2, "%s: permission denied: %s\n", err, from);
		else if (nbr == NO_DIR)
			ft_dprintf(2, "%s: not a directory: %s\n", err, from);
		else if (nbr == IS_DIR)
			ft_dprintf(2, "%s: is a directory: %s\n", err, from);
		else if (nbr == EXC_FORM)
			ft_dprintf(2, "%s: exec format error: %s\n", err, from);
		else if (nbr == FORK_ERR)
			ft_dprintf(2, "%s: can not creat new process: %s\n", err, from);
		else if (nbr == SIG_TERM)
			exit_signal();
	}
}
