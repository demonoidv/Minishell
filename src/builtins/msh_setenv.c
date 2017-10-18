/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:45:12 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/18 16:24:27 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_var(char **new, char ****env)
{
	int		i;
	char	***tmp;

	i = 0;
	tmp = (char***)malloc(sizeof(char**) * (count_var(*env) + 2));
	while (*env && (*env)[i])
	{
		tmp[i] = (*env)[i];
		i++;
	}
	if ((tmp[i] = (char**)malloc(sizeof(char*) * 3)))
	{
		tmp[i][0] = ft_strdup(new[0]);
		tmp[i][1] = ft_strdup(new[1]);
		tmp[i][2] = NULL;
	}
	tmp[i + 1] = NULL;
	ft_memdel((void**)env);
	*env = tmp;
}

static void		replace_value(char **new, char ***env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strcmp(env[i][0], new[0]))
		i++;
	if (env[i])
	{
		ft_strdel(&(env[i][1]));
		if (new[1])
			env[i][1] = ft_strdup(new[1]);
	}
}

void			edit_env(char *arg, char ****env)
{
	int		i;
	char	**new_var;

	i = 1;
	new_var = ft_strsplit(arg, '=');
	while (new_var[1] && new_var[++i])
		new_var[1] = ft_strjoin_free(new_var[1], new_var[i], 3);
	if (new_var[1])
		new_var[2] = NULL;
	if (search_var(*env, new_var[0]))
		replace_value(new_var, *env);
	else
		add_var(new_var, env);
	ft_strdel(&(new_var[0]));
	ft_strdel(&(new_var[1]));
	ft_memdel((void**)&new_var);
}

void			msh_setenv(char **arg, char ****env)
{
	int		i;

	i = 0;
	while (arg[i] && ft_strchr(arg[i], '=') && arg[i][0] != '=')
	{
		edit_env(arg[i], env);
		i++;
	}
	if (arg[i])
		msh_error(STX_ERR, arg[i], SENV_ERR);
}
