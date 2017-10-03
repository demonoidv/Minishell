/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_switch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 01:23:37 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_switch(char **cmdtab)
{
	int		i;

	i = 0;
	if (!ft_strcmp(cmdtab[0], "exit"))
		msh_exit(&(cmdtab[1]));
	else if (!ft_strcmp(cmdtab[0], "cd"))
		ft_putendl("Ceci est un cd");
}
