/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 17:38:14 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/22 17:05:24 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	countvar(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	return (i);
}

char		***get_env(char **environ)
{
	int		i;
	char	***env;

	i = 0;
	env = (char***)malloc(sizeof(char**) * (countvar(environ) + 1));
	while (environ[i])
	{
		env[i] = ft_strsplit(environ[i], '=');
		i++;
	}
	env[i] = NULL;
	return (env);
}
