/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:28:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/30 22:43:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static int	lateral_flitch(char *event, char *cmd, int pos)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = CURSOR_X(get_cursor_pos());
	if (!ft_strcmp(event, "\033[C") && cmd && cmd[pos])
	{
		if (cmd[pos] == '\t')
			event = "\t";
		ft_putstr(event);
		if (cmd[pos] == '\n')
			ft_printf("\033[%d;1H", x + 1);
		pos++;
	}
	else if (!ft_strcmp(event, "\033[D") && pos > 0)
	{
		ft_putstr(event);
		i = ((pos--) - 1);
		if (cmd[pos] == '\n')
		{
			while (i >= 0 && cmd[i] != '\n')
			{
				i--;
				j++;
			}
			ft_printf("\033[%d;%dH", x - 1, 5);
		}
	}
	return (pos);
}

static int	flitch_event(char *event, char **cmd, int pos, unsigned long curs)
{
	if (!ft_strcmp(event, "\033[A") || !ft_strcmp(event, "\033[B"))
	{
		if (*cmd && **cmd)
			clean_line(*cmd, curs, DEFAULT);
		ft_strdel(cmd);
		if (event[2] == 'A')
			prev_cmd(cmd, PREV_CMD);
		else
			prev_cmd(cmd, NEXT_CMD);
		ft_putstr(*cmd);
		pos = ft_strlen(*cmd);
	}
	pos = lateral_flitch(event, *cmd, pos);
	return (pos);
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
	else if (!ft_strcmp(tmp, "\033[3") && read(0, buff, 1) && buff[0] == '~')
		*cmd = del_frontchar(*cmd, pos, curs);
	ft_strdel(&tmp);
	return (pos);
}
