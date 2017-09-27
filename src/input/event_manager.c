/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:28:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/27 16:07:21 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	flitch_event(char *event, char **cmd, int pos)
{
	if (!ft_strcmp(event, "\033[A") || !ft_strcmp(event, "\033[B"))
	{
		if (*cmd && **cmd)
			clean_line(*cmd, pos);
		ft_strdel(cmd);
		if (event[2] == 'A')
			prev_cmd(cmd, PREV_CMD);
		else
			prev_cmd(cmd, NEXT_CMD);
		if (*cmd)
		{
			ft_putstr(*cmd);
			pos = ft_strlen(*cmd);
		}
	}
	else if (!ft_strcmp(event, "\033[C") && *cmd && (*cmd)[pos])
	{
		ft_putstr(event);
		pos++;
	}
	else if (!ft_strcmp(event, "\033[D") && pos > 0)
	{
		ft_putstr(event);
		pos--;
	}
	return (pos);
}

int			event_manager(char **cmd, int pos, char *c)
{
	char	buff[3];
	char	*tmp;

	ft_bzero(buff, 3);
	if (*c == 127)
	{
		if (pos > 0)
		{
			*cmd = del_char(*cmd, pos);
			return (pos - 1);
		}
		return (pos);
	}
	read(0, buff, 2);
	tmp = ft_strjoin(c, buff);
	if (tmp[1] == '[' && tmp[2] >= 'A' && tmp[2] <= 'D')
		pos = flitch_event(tmp, cmd, pos);
	else if (!ft_strcmp(tmp, "\033[3") && read(0, buff, 1) && buff[0] == '~')
		*cmd = del_frontchar(*cmd, pos);
	ft_strdel(&tmp);
	return (pos);
}
