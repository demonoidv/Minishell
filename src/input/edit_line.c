/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:18:46 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/02 23:49:58 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_char(char *cmd, int pos, unsigned long curs)
{
	int		i;
	char	*tmp;

	i = 0;
	if (pos > 0)
	{
		tmp = ft_strdup(&cmd[pos]);
		cmd[pos - 1] = '\0';
		cmd = ft_strjoin_free(cmd, tmp, 3);
		clean_line(cmd, curs, DEFAULT);
		ft_putstr(cmd);
		clean_line(cmd, curs, 2);
		while (i + 1 < pos && cmd[i])
		{
			ft_putchar(cmd[i]);
			i++;
		}
	}
	return (cmd);
}

char	*del_frontchar(char *cmd, int pos, unsigned long curs)
{
	int		i;
	char	*tmp;

	i = 0;
	if (cmd && cmd[pos])
	{
		tmp = ft_strdup(&cmd[pos + 1]);
		cmd[pos] = '\0';
		cmd = ft_strjoin_free(cmd, tmp, 3);
		clean_line(cmd, curs, DEFAULT);
		ft_putstr(cmd);
		clean_line(cmd, curs, 2);
		while (i < pos)
		{
			ft_putchar(cmd[i]);
			i++;
		}
	}
	return (cmd);
}
