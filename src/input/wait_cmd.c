/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/26 18:55:55 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void		msh_prompt(char *pwd, char mode)
{
	int		i;

	if (mode == DEFAULT && pwd)
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
}

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
	char	buff[2];
	char	*cmd;

	i = 0;
	set_term_param(CMD);
	cmd = NULL;
	ft_bzero(buff, 2);
	while (buff[0] != '\n' && read(0, buff, 1))
	{
		if ((buff[0] >= 1 && buff[0] <= 6) || (buff[0] >= 14 && buff[0] <= 31)\
		|| buff[0] == 127)
			i = event_manager(&cmd, i, (char*)buff);
		else if (buff[0] != '\n')
		{
			ft_putchar(buff[0]);
			if (cmd && cmd[i])
				cmd[i] = buff[0];
			else
				cmd = ft_strjoin_free(cmd, (char*)buff, 1);
			i++;
		}
	}
	ft_putstr("\v\r");
	set_term_param(DEFAULT);
	return (cmd);
}

static char		*get_cmd_quote(char *cmd, char quote)
{
	char	*tmp;

	tmp = NULL;
	msh_prompt(NULL, quote);
	tmp = get_cmd_line();
	cmd = ft_strjoin_free(cmd, "\n", 1);
	if (tmp)
		cmd = ft_strjoin_free(cmd, tmp, 3);
	return (cmd);
}

void			wait_cmd(char ***env)
{
	char	quote;
	char	*cmdline;

	quote = DEFAULT;
	msh_prompt(search_var(env, "PWD"), quote);
	cmdline = get_cmd_line();
	while ((quote = check_escape(cmdline)))
		cmdline = get_cmd_quote(cmdline, quote);
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
