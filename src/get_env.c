/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 17:38:14 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/14 16:26:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_onlyone_value(char **var)
{
	int		i;

	i = 2;
	while (var[i])
	{
		var[1] = ft_strjoin_free(ft_strjoin_free(var[1], "=", 1), var[i], 3);
		i++;
	}
}

char			***get_env(char **environ)
{
	int		i;
	char	***env;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if ((env = (char***)malloc(sizeof(char**) * \
	(count_var((char***)environ) + 1))))
	{
		while (environ[i])
		{
			env[i] = ft_strsplit(environ[i], '=');
			if (msh_tablen(env[i]) > 2)
				get_onlyone_value(env[i]);
			i++;
		}
		env[i] = NULL;
		if (i && (tmp = ft_strjoin_free("SHLVL=", \
		ft_itoa((ft_atoi(search_var(env, "SHLVL"))) + 1), 2)))
			edit_env(tmp, &env);
		else if (!(env[i]))
			edit_env("SHLVL=1", &env);
		ft_strdel(&tmp);
	}
	return (env);
}
