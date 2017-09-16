/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/16 18:14:48 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(char **cmd)
{
	char	buff[2];

	ft_putstr("$>");
	while (read(0, buff, BUFF_SIZE) >= 0 && buff[0] != '\n')
	{
		ft_putnbr((int)buff[0]);
		*cmd = ft_strjoin_free(*cmd, buff, 1);
		if (!ft_strcmp(*cmd, "exit"))
		{
			ft_strdel(cmd);
			exit(0);
		}
		ft_strdel(cmd);
	}
	wait_cmd(cmd);
}
