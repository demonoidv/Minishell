/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/17 23:21:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		msh_prompt(char ***env);
{
	int		i;
	char	*pwd;

	if ((pwd = search_var(env, "PWD")))
	{
		i = ft_strlen(pwd);
		while (i >= 0 && pwd[i] != '/')
			i--;
		if (pwd[i] == '/' && ft_strcmp(pwd, "/"))
			i++;
		ft_printf("\033[42m%s %C ", &(pwd[i]), 50377);
	}
}

void			wait_cmd(char **cmd)
{
	int		i;
	char	*line;
	char	***env;

	i = 0;
	line = NULL;
	env = get_env();
	ft_putstr();
	if (get_next_line(0, &line))
	{
		*cmd = ft_strtrim(line);

		if (ft_countchar())
	}
	wait_cmd(cmd);
	ft_strdel(cmd);
}
