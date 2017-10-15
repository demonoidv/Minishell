/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 05:40:13 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 14:25:54 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		***env_cpy(char ***env)
{
	int		i;
	char	***new;

	i = 0;
	new = NULL;
	if (env && (new = (char***)malloc(sizeof(char**) * (count_var(env) + 1))))
	{
		while (env[i])
		{
			new[i] = (char**)malloc(sizeof(char*) * 3);
			new[i][0] = ft_strdup(env[i][0]);
			new[i][1] = ft_strdup(env[i][1]);
			new[i][2] = NULL;
			i++;
		}
		new[i] = NULL;
	}
	return (new);
}

static void		display_env(char ***env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		ft_printf("%s=%s\n", env[i][0], env[i][1]);
		i++;
	}
}

void			msh_env(char **arg, char ***env)
{
	int		i;
	char	**clean_env;

	i = 0;
	clean_env = NULL;
	if (arg[i] && !ft_strcmp(arg[i], "-i"))
	{
		env = &clean_env;
		i++;
	}
	else
		env = env_cpy(env);
	while (arg[i] && ft_strchr(arg[i], '='))
	{
		edit_env(arg[i], &env);
		i++;
	}
	if (arg[i] && !ft_strcmp(arg[i], "env"))
		msh_env(&(arg[i + 1]), env);
	else if (arg[i])
		msh_error(msh_exec(&(arg[i]), env), arg[i], ENV_ERR);
	else
		display_env(env);
	del_env(&env);
}
