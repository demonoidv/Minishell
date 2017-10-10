/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/10 01:21:01 by vsporer          ###   ########.fr       */
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

void			msh_error(int nbr, char *from, int funcnum)
{
	char	*err;

	err = check_funcnum(funcnum);
	if (from && nbr)
	{
		if (nbr == NO_FILE)
			ft_printf("%s: no such file or directory: %s\n", err, from);
		else if (nbr == TM_ARGS)
			ft_printf("%s: too many arguments\n", from);
		else if (nbr == NO_CMD)
			ft_printf("%s: command not found: %s\n", err, from);
		else if (nbr == STX_ERR)
			ft_printf("%s: %s: syntax error\n", err, from);
		else if (nbr == VAR_NSET)
			ft_printf("%s: %s not set\n", err, from);
		else if (nbr == PERM_DEN)
			ft_printf("%s: %s: permission denied\n", err, from);
		else if (nbr == NO_DIR)
			ft_printf("%s: not a directory: %s\n", err, from);
	}
}
