/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:18:46 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 18:01:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_char(char *cmd, int pos)
{
	int		len;
	char	*tmp;

	if (pos > 0)
	{
		tmp = ft_strdup(&cmd[pos]);
		cmd[pos - 1] = '\0';
		cmd = ft_strjoin_free(cmd, tmp, 3);
		clean_line(cmd, pos);
		ft_putstr(cmd);
		len = ft_strlen(cmd);
		while (len >= pos)
		{
			ft_putchar('\b');
			len--;
		}
	}
	return (cmd);
}

char	*del_frontchar(char *cmd, int pos)
{
	int		len;
	char	*tmp;

	if (cmd && cmd[pos])
	{
		tmp = ft_strdup(&cmd[pos + 1]);
		cmd[pos] = '\0';
		cmd = ft_strjoin_free(cmd, tmp, 3);
		clean_line(cmd, pos);
		ft_putstr(cmd);
		len = ft_strlen(cmd);
		while (len > pos)
		{
			ft_putchar('\b');
			len--;
		}
	}
	return (cmd);
}
