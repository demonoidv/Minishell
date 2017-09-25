/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 16:47:12 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/24 17:26:26 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_squote(char **cmd)
{
	char	buff[2];

	while (read(0, buff, 1) && (buff[0] != '\'' || \
	(buff[0] == '\'' && check_escape(*cmd))))
	{
		if (buff[0] == '\n')
			ft_putstr("quote> ");
		*cmd = ft_strjoin_free(*cmd, (char*)buff, 1);
	}
}

static void		get_dquote(char **cmd)
{
	char	buff[2];

	while (read(0, buff, 1) && (buff[0] != '"' || \
	(buff[0] == '"' && check_escape(*cmd))))
	{
		if (buff[0] == '\n')
			ft_putstr("dquote> ");
		*cmd = ft_strjoin_free(*cmd, (char*)buff, 1);
	}
}

char			**get_quote(char **cmd, int pos, char quote)
{
	if (cmd && cmd[pos] && (cmd[pos][ft_strlen(cmd[pos]) - 1] == ' ' || \
	cmd[pos][ft_strlen(cmd[pos]) - 1] == '\t'))
	{
		cmd = ft_addstrtab(&cmd, 1);
		pos++;
	}
	if (quote == '"')
		get_dquote(&(cmd[pos]));
	else if (quote == '\'')
		get_squote(&(cmd[pos]));
	return (cmd);
}
