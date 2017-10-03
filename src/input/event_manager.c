/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:28:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 00:19:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static int	right_flitch(char *cmd, int pos)
{
	int				x;
	struct winsize	ws;

	x = CURSOR_X(get_cursor_pos());
	ioctl(0, TIOCGSIZE, &ws);
	if (cmd && cmd[pos])
	{
		if (cmd[pos] == '\n' || (CURSOR_Y(get_cursor_pos())) == ws.ws_col)
			ft_printf("\033[%d;1H", x + 1);
		else
			ft_putchar(cmd[pos]);
		pos++;
	}
	return (pos);
}

static int	left_flitch(char *event, char *cmd, int pos, unsigned long curs)
{
	int				i;
	int				x;

	i = 0;
	x = CURSOR_X(get_cursor_pos());
	if (pos > 0)
	{
		ft_putstr(event);
		i = (--pos) - 1;
		if (cmd[pos] == '\n')
		{
			while (i >= 0 && cmd[i] != '\n')
				i--;
			if ((x - 1) == CURSOR_X(curs))
				ft_printf("\033[%d;%dH", x - 1, \
				(pos + CURSOR_Y(curs)) - (i + 1));
			else
				ft_printf("\033[%d;%dH", x - 1, pos - i);
		}
	}
	return (pos);
}

static int	flitch_event(char *event, char **cmd, int pos, unsigned long curs)
{
	if ((!ft_strcmp(event, "\033[A") || !ft_strcmp(event, "\033[B")) && \
	!(curs & NO_HISTORY))
	{
		clean_line(*cmd, curs, DEFAULT);
		ft_strdel(cmd);
		if (event[2] == 'A')
			prev_cmd(cmd, PREV_CMD);
		else
			prev_cmd(cmd, NEXT_CMD);
		ft_putstr(*cmd);
		pos = ft_strlen(*cmd);
	}
	if (*cmd)
	{
		ft_putstr("\033[s");
		clean_line(*cmd, curs, 2);
		curs = get_cursor_pos();
		ft_putstr("\033[u");
		if (!ft_strcmp(event, "\033[C") && !ft_strchr(*cmd, '\t'))
			pos = right_flitch(*cmd, pos);
		else if (!ft_strcmp(event, "\033[D") && !ft_strchr(*cmd, '\t'))
			pos = left_flitch(event, *cmd, pos, curs);
	}
	return (pos);
}

static int	home_end_event(char *event, char **cmd, unsigned long curs)
{
	if (!ft_strcmp(event, "\033[H"))
	{
		clean_line(*cmd, curs, 2);
		return (0);
	}
	else
	{
		clean_line(*cmd, curs, DEFAULT);
		ft_putstr(*cmd);
		return (ft_strlen(*cmd));
	}
}

int			event_manager(char **cmd, int pos, char *c, unsigned long curs)
{
	char	buff[3];
	char	*tmp;

	ft_bzero(buff, 3);
	if (*c == 127)
	{
		if (pos > 0)
		{
			*cmd = del_char(*cmd, pos, curs);
			return (pos - 1);
		}
		return (pos);
	}
	read(0, buff, 2);
	tmp = ft_strjoin(c, buff);
	if (tmp[1] == '[' && tmp[2] >= 'A' && tmp[2] <= 'D')
		pos = flitch_event(tmp, cmd, pos, curs);
	else if (!ft_strcmp(tmp, "\033[H") || !ft_strcmp(tmp, "\033[F"))
		pos = home_end_event(tmp, cmd, curs);
	else if (!ft_strcmp(tmp, "\033[3") && read(0, buff, 1) && buff[0] == '~')
		*cmd = del_frontchar(*cmd, pos, curs);
	ft_strdel(&tmp);
	return (pos);
}
