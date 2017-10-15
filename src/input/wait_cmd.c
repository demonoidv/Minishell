/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 03:02:18 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long	msh_prompt(char mode)
{
	int		i;
	char	*pwd;

	pwd = NULL;
	if (mode == DEFAULT && (pwd = getcwd(pwd, 0)))
	{
		i = ft_strlen(pwd);
		while (i >= 0 && pwd[i] != '/')
			i--;
		if (pwd[i] == '/' && ft_strcmp(pwd, "/"))
			i++;
		ft_printf("\033[32;44m%s\033[0m\033[32m =>\033[0m ", &(pwd[i]));
	}
	else if (mode == QUOTE)
		ft_putstr("quote> ");
	else if (mode == DQUOTE)
		ft_putstr("dquote> ");
	else if (mode == -1)
		ft_putstr("> ");
	else
		ft_putstr("\033[32m=>\033[0m ");
	return (get_cursor_pos());
}

static void			new_cmd_line(char *cmd, unsigned long curs)
{
	clean_line(cmd, curs, DEFAULT);
	ft_putstr(cmd);
	ft_putstr("\v\r");
}

static char			*get_cmd_line(unsigned long curs)
{
	int		i;
	char	buff[2];
	char	*cmd;

	i = 0;
	cmd = NULL;
	ft_bzero(buff, 2);
	while (buff[0] != '\n' && read(0, buff, 1))
	{
		if ((buff[0] >= 1 && buff[0] <= 6) || (buff[0] >= 14 && buff[0] <= 31)\
		|| buff[0] == 127)
			i = event_manager(&cmd, i, (char*)buff, curs);
		else if (buff[0] != '\n')
		{
			if (buff[0] != '\t' || !cmd || (cmd && !cmd[i]))
				ft_putchar(buff[0]);
			if (cmd && cmd[i] && buff[0] != '\t')
				cmd[i++] = buff[0];
			else if (!cmd || (cmd && !cmd[i]))
			{
				cmd = ft_strjoin_free(cmd, (char*)buff, 1);
				i++;
			}
		}
	}
	new_cmd_line(cmd, curs);
	return (cmd);
}

static char			*get_cmd_quote(char *cmd, char quote)
{
	char			*tmp;
	unsigned long	curs;

	tmp = NULL;
	curs = msh_prompt(quote);
	tmp = get_cmd_line((curs | NO_HISTORY));
	cmd = ft_strjoin_free(cmd, "\n", 1);
	if (tmp)
		cmd = ft_strjoin_free(cmd, tmp, 3);
	return (cmd);
}

static void			exec_switch(char **cmdline, char ****env)
{
	int		i;
	char	**cmdtab;
	char	**multicmd;

	i = 0;
	prev_cmd(cmdline, DEFAULT);
	multicmd = next_cmdline(*cmdline);
	while (multicmd && multicmd[i] && exit_value(0, CHECK) < 0)
	{
		cmdtab = line_to_tab(multicmd[i], *env);
		msh_error(msh_switch(cmdtab, env), cmdtab[0], DEFAULT);
		del_cmdtab(&cmdtab);
		ft_strdel(&(multicmd[i]));
		i++;
	}
	while (multicmd && multicmd[i])
	{
		ft_strdel(&(multicmd[i]));
		i++;
	}
	ft_memdel((void**)&multicmd);
}

void				wait_cmd(char ****env)
{
	char			quote;
	char			*cmdline;
	unsigned long	curs;

	quote = DEFAULT;
	set_term_param(CMD);
	curs = msh_prompt(quote);
	cmdline = get_cmd_line(curs);
	while ((quote = check_escape(cmdline)))
		cmdline = get_cmd_quote(cmdline, quote);
	set_term_param(DEFAULT);
	clean_line(NULL, 0, 1);
	if (cmdline && cmdline[0])
		exec_switch(&cmdline, env);
	ft_strdel(&cmdline);
	if (exit_value(0, CHECK) < 0)
		wait_cmd(env);
}
