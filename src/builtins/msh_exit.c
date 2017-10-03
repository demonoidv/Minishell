/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:52:11 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 02:27:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void		msh_exit(char **arg)
{
	char	ret;

	ret = 0;
	if (msh_tablen(arg) > 1)
		msh_error(TM_ARGS, "exit");
	else if (arg[0])
		exit((char)ft_atoi(arg[0]));
	else
		exit(0);
}
