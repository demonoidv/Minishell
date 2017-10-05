/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/05 18:22:51 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_switch(char **cmdtab, char ****env)
{
	int		i;

	i = 0;
	if (!ft_strcmp(cmdtab[0], "exit"))
		msh_exit(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "cd"))
		ft_putendl("Ceci est un cd");
	else if (!ft_strcmp(cmdtab[0], "env"))
		msh_env(&(cmdtab[1]), *env);
	else if (!ft_strcmp(cmdtab[0], "setenv"))
		msh_setenv(&(cmdtab[1]), env);
	else
		return (NO_CMD);
	return (0);
}