/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/21 22:13:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static char		*check_funcnum(int funcnum)
{
	if (funcnum > 0 && funcnum <= 4)
		exit_value(1, (SET | STATEXIT));
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

static char		*signal_message(int sig)
{
	char	*(msgtab[13]);

	msgtab[SIGQUIT] = "%d quit \t%s\n";
	msgtab[SIGILL] = "%d illegal instruction \t%s\n";
	msgtab[SIGKILL] = "%d killed \t%s\n";
	msgtab[SIGHUP] = "%d hang up \t%s\n";
	msgtab[SIGTRAP] = "%d trace trap \t%s\n";
	msgtab[SIGABRT] = "%d abort \t%s\n";
	msgtab[SIGEMT] = "%d emulate instruction executed \t%s\n";
	msgtab[SIGFPE] = "%d floating-point exception \t%s\n";
	msgtab[SIGBUS] = "%d bus error \t%s\n";
	msgtab[SIGSEGV] = "%d segmentation fault \t%s\n";
	msgtab[SIGSYS] = "%d non-existent system call invoked \t%s\n";
	return (msgtab[sig]);
}

static char		*error_message(int nbr)
{
	char	*(msgtab[10]);

	msgtab[0] = "%s: no such file or directory: %s\n";
	msgtab[1] = "%s: too many arguments\n";
	msgtab[2] = "%s: command not found: %s\n";
	msgtab[3] = "%s: syntax error: %s\n";
	msgtab[4] = "%s: %s not set\n";
	msgtab[5] = "%s: permission denied: %s\n";
	msgtab[6] = "%s: not a directory: %s\n";
	msgtab[7] = "%s: is a directory: %s\n";
	msgtab[8] = "%s: exec format error: %s\n";
	msgtab[9] = "%s: can not creat new process: %s\n";
	return (msgtab[nbr - 1]);
}

void			msh_error(int nbr, char *from, int funcnum)
{
	int		sig;
	char	*err;

	if (from && nbr && nbr != SIG_TERM)
	{
		err = check_funcnum(funcnum);
		if (nbr == NO_CMD && funcnum == ENV_ERR)
			nbr = NO_FILE;
		if (nbr == TM_ARGS)
			ft_dprintf(2, error_message(nbr), from);
		else if (nbr <= 10)
			ft_dprintf(2, error_message(nbr), err, from);
	}
	else if (from && nbr == SIG_TERM)
	{
		sig = exit_value(-1, (CHECK | SIGEXIT));
		from = save_cmdline(NULL, CHECK);
		if (sig == SIGINT)
		{
			signal_value(0);
			ft_putchar('\n');
		}
		else if (sig && sig != SIGINT && sig <= 12)
			ft_dprintf(2, signal_message(sig), last_pid(0), from);
	}
}
