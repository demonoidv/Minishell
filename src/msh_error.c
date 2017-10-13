/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/13 12:42:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	ret = exit_value(-1, (CHECK | SIGEXIT));
	ft_dprintf(2, "Signal interruption code: %d\n", ret);
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
