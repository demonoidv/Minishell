/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/23 02:59:15 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		msh_prompt(char ***env)
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
		ft_printf("\033[32;44m%s\033[0m\033[32m =>\033[0m ", &(pwd[i]));
	}
	else
		ft_putstr("\033[32m=>\033[0m ");
}

static int		check_quote(char *line, int i)
{
	int		count_bs;

	count_bs = 0;
	if (line && line[i])
	{
		while (i >= 0)
		{
			if (line[--i] == '\\')
				count_bs++;
		}
	}
	return (count_bs % 2);
}

static char		**get_cmd_line(void)
{
	char	*line;
	char	*lcmd;
	char	*quote;
	char	*end_quote;

	lcmd = NULL;
	get_next_line(0, &line);
	if ((quote = ft_strchr(line, '"')) && !check_quote(line, quote - line))
	{
		while (!ft_strchr(quote + 1, '"') || ((end_quote = \
		ft_strchr(quote + 1, '"')) && check_quote(line, end_quote - line)))
		{
			ft_putstr("quote> ");
			get_next_line(0, &line);
			quote = line - 1;
			lcmd = ft_strjoin_free(lcmd, line, 3);
		}
		return (ft_split_whitespaces(lcmd));
	}
	return (ft_split_whitespaces(line));
}

void			wait_cmd(char ***env)
{
	int		i;
	char	**cmd;

	i = 0;
	msh_prompt(env);
	cmd = get_cmd_line();
	if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_strdel(cmd);
		exit(0);
	}
	ft_strdel(cmd);
	wait_cmd(env);
}
