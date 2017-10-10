/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 17:38:14 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/10 00:34:56 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	countvar(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char		***get_env(char **environ)
{
	int		i;
	char	***env;
	char	*tmp;

	i = 0;
	tmp = NULL;
	env = (char***)malloc(sizeof(char**) * (countvar(environ) + 1));
	while (environ[i])
	{
		env[i] = ft_strsplit(environ[i], '=');
		i++;
	}
	env[i] = NULL;
	if (i && (tmp = ft_strjoin_free("SHLVL=", \
	ft_itoa((ft_atoi(search_var(env, "SHLVL"))) + 1), 2)))
		edit_env(tmp, &env);
	else if (!(env[i]))
		edit_env("SHLVL=1", &env);
	ft_strdel(&tmp);
	return (env);
}
