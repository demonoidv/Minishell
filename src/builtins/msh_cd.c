/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 03:59:19 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/10 01:19:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		move_wd(char *path, char ****env)
{
	char			*tmp;
	struct stat		st;

	tmp = NULL;
	if (access(path, F_OK) == -1)
		msh_error(NO_FILE, path, CD_ERR);
	else if (!(stat(path, &st)) && !S_ISDIR(st.st_mode))
		msh_error(NO_DIR, path, CD_ERR);
	else if (access(path, X_OK) == -1)
		msh_error(PERM_DEN, path, CD_ERR);
	else
	{
		tmp = getcwd(NULL, 0);
		if (chdir(path))
			msh_error(NO_DIR, path, CD_ERR);
		else
		{
			tmp = ft_strjoin_free("OLDPWD=", tmp, 2);
			edit_env(tmp, env);
		}
		ft_strdel(&tmp);
	}
	tmp = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
	edit_env(tmp, env);
	ft_strdel(&tmp);
}

void			msh_cd(char **arg, char ****env)
{
	char	*path;

	path = NULL;
	if (msh_tablen(arg) > 1)
		msh_error(TM_ARGS, "cd", CD_ERR);
	else if (!arg[0] || (arg[0] && (!ft_strcmp(arg[0], "-") || \
	!ft_strcmp(arg[0], "--"))))
	{
		if ((!arg[0] || (arg[0] && !ft_strcmp(arg[0], "--"))) && \
		!(path = search_var(*env, "HOME")))
			msh_error(VAR_NSET, "HOME", CD_ERR);
		else if (arg[0] && !ft_strcmp(arg[0], "-") && \
		!(path = search_var(*env, "OLDPWD")))
			msh_error(VAR_NSET, "OLDPWD", CD_ERR);
	}
	else if (arg[0])
		path = arg[0];
	if (path)
		move_wd(path, env);
}
