/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 04:33:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

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

/*
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
*/

static void		set_term_param(int mode)
{
	struct termios			term;
	static struct termios	save;

	if (mode == CMD && !tcgetattr(0, &term))
	{
		save = term;
		if (term.c_lflag & ECHO)
			term.c_lflag = term.c_lflag ^ ECHO;
		if (term.c_lflag & ICANON)
			term.c_lflag = term.c_lflag ^ ICANON;
		term.c_cc[VMIN] = 1;
	}
	else if (mode == DEFAULT)
		term = save;
	tcsetattr(0, TCSANOW, &term);
}

static char		*get_cmd_line(void)
{
	int		i;
	int		len;
	char	buff[2];
	char	*cmd;

	i = 0;
	len = 0;
	set_term_param(CMD);
	cmd = NULL;
	ft_bzero(buff, 2);
	while (read(0, buff, 1))
	{
//			if (buff[0] == '\033' && read(0, buff, 1) && buff[0] == '[' && read(0, buff, 1) && buff[0] == 'D')
		if (buff[0] == '\033')
			i = event_manager(&cmd, i);
		else
		{
			if (buff[0] == 127 && i > 0 && cmd)
			{
				clean_line(cmd, i);
				cmd = del_char(cmd, i);
				ft_putstr(cmd);
				len = ft_strlen(cmd);
				i--;
				while (len > i)
				{
					ft_putchar('\b');
					len--;
				}
			}
			else if (buff[0] != 127)
				ft_putchar(buff[0]);
/*			cmd = ft_addchar(&cmd, 1);
			if (i && (buff[0] == ' ' || buff[0] == '\t'))
			{
				cmd = ft_addstrtab(&cmd, 1);
				cmd[++i] = NULL;
			}
			while (buff[0] == ' ' || buff[0] == '\t')
				read(0, buff, 1);
			if ((buff[0] == '\'' || buff[0] == '"') && \
			!check_escape(cmd[i]))
				cmd = get_quote(cmd, i, buff[0]);*/
			if (buff[0] != '\n' && buff[0] != '\033' && buff[0] != 127)
			{
				if (cmd && cmd[i])
					cmd[i] = buff[0];
				else
					cmd = ft_strjoin_free(cmd, (char*)buff, 1);
				i++;
			}
			else if (buff[0] == '\n')
				return (cmd);
		}
	}
	return (cmd);
}

void			wait_cmd(char ***env)
{
	int		i;
	char	*cmdline;

	i = 0;
	msh_prompt(env);
	cmdline = get_cmd_line();
	if (cmdline && cmdline[0])
	{
		if (!ft_strcmp(cmdline, "exit"))
		{
			ft_strdel(&cmdline);
			exit(0);
		}
	}
	ft_strdel(&cmdline);
	wait_cmd(env);
}
