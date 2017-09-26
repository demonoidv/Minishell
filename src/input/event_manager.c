/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:28:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 18:03:39 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		event_manager(char **cmd, int pos, char *c)
{
	char	buff[3];
	char	*tmp;

	ft_bzero(buff, 3);
	if (*c == 127 && pos > 0)
	{
		*cmd = del_char(*cmd, pos);
		return (pos - 1);
	}
	read(0, buff, 2);
	tmp = ft_strjoin(c, buff);
/*	if (!ft_strcmp(tmp, "\033[A"))
	else if (!ft_strcmp(tmp, "\033[B"))
	else */if (!ft_strcmp(tmp, "\033[C") && *cmd && (*cmd)[pos])
	{
		ft_putstr(tmp);
		pos++;
	}
	else if (!ft_strcmp(tmp, "\033[D") && pos > 0)
	{
		ft_putstr(tmp);
		pos--;
	}
	else if (!ft_strcmp(tmp, "\033[3") && read(0, buff, 1) && buff[0] == '~')
		*cmd = del_frontchar(*cmd, pos);
	return (pos);
}
