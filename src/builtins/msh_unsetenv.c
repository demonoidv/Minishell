/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 20:27:27 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/07 20:47:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		del_var(char *arg, char ***env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strcmp(env[i][0], arg))
		i++;
	if (env[i])
	{
		ft_strdel(&(env[i][0]));
		ft_strdel(&(env[i][1]));
		ft_memdel((void**)&(env[i]));
		i++;
	}
	while (env[i])
	{
		ft_swap_ptr((void**)&(env[i - 1]), (void**)&(env[i]));
		i++;
	}
}

void			msh_unsetenv(char **arg, char ****env)
{
	int		i;

	i = 0;
	while (*env && arg[i])
	{
		del_var(arg[i], *env);
		i++;
	}
}
