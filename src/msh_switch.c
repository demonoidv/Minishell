/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/07 21:25:16 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_switch(char **cmdtab, char ****env)
{
	int		i;

	i = 0;
	if (!ft_strcmp(cmdtab[0], "exit"))
		msh_exit(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "echo"))
		msh_echo(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "cd"))
		msh_cd(*env);
	else if (!ft_strcmp(cmdtab[0], "env"))
		msh_env(&(cmdtab[1]), *env);
	else if (!ft_strcmp(cmdtab[0], "setenv"))
		msh_setenv(&(cmdtab[1]), env);
	else if (!ft_strcmp(cmdtab[0], "unsetenv"))
		msh_unsetenv(&(cmdtab[1]), env);
	else
		return (NO_CMD);
	return (0);
}
