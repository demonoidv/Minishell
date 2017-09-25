/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:28:03 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 03:52:55 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		event_manager(char **cmd, int pos)
{
	char	buff[3];

	ft_bzero(buff, 3);
	read(0, buff, 2);
/*	if (!ft_strcmp(buff, "[A"))
	else if (!ft_strcmp(buff, "[B"))
	else */if (!ft_strcmp(buff, "[C") && *cmd && (*cmd)[pos])
	{
		ft_putchar((*cmd)[pos]);
		pos++;
	}
	else if (!ft_strcmp(buff, "[D") && pos > 0)
	{
		ft_putchar('\b');
		pos--;
	}
	if (!*cmd)
		*cmd = NULL;
	return (pos);
}
