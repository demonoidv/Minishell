/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/05 17:55:05 by vsporer          ###   ########.fr       */
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
			ft_printf("%s: %s: No such file or directory\n", err, from);
		else if (nbr == TM_ARGS)
			ft_printf("%s: too many arguments\n", from);
		else if (nbr == NO_CMD)
			ft_printf("%s: %s: command not found\n", err, from);
		else if (nbr == STX_ERR)
			ft_printf("%s: %s: syntax error\n", err, from);
	}
}
