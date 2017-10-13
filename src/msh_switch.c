/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/13 14:12:35 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_switch(char **cmdtab, char ****env)
{
	msh_signal();
	if (!ft_strcmp(cmdtab[0], "exit"))
		msh_exit(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "echo"))
		msh_echo(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "cd"))
		msh_cd(&(cmdtab[1]), env);
	else if (!ft_strcmp(cmdtab[0], "env"))
		msh_env(&(cmdtab[1]), *env);
	else if (!ft_strcmp(cmdtab[0], "setenv"))
		msh_setenv(&(cmdtab[1]), env);
	else if (!ft_strcmp(cmdtab[0], "unsetenv"))
		msh_unsetenv(&(cmdtab[1]), env);
	else
		return (msh_exec(cmdtab, *env));
	return (0);
}
