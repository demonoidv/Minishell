/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:19:16 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/26 18:56:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		clean_line(char *cmd, int pos)
{
	int		len;

	len = ft_strlen(cmd);
	while (pos <= len + 1)
	{
		ft_putchar(127);
		pos++;
	}
	while (pos >= 0)
	{
		ft_putstr("\033[D");
		ft_putchar(127);
		if (--pos)
			ft_putstr("\033[D");
	}
}

static int	search_end_quote(char *line, int pos, char quote)
{
	int		count_bs;

	count_bs = 0;
	pos++;
	while (line[pos] && line[pos] != quote)
		pos++;
	if (line[pos] && quote)
	{
		while (pos - 1 >= 0 && line[pos - 1] == '\\')
		{
			count_bs++;
			pos--;
		}
		if (!(count_bs % 2))
			return (pos + count_bs);
		if (line[pos + count_bs])
			return (search_end_quote(line, pos + count_bs, quote));
	}
	return (0);
}

char		check_escape(char *line)
{
	int		i;
	char	quote;
	int		count_bs;

	i = 0;
	while (line && line[i])
	{
		count_bs = 0;
		if (line[i] == '"' || line[i] == '\'' || !line[i + 1])
		{
			quote = line[i] == '"' || line[i] == '\'' ? line[i] : 0;
			while (i - 1 >= 0 && line[i - 1] == '\\')
			{
				count_bs++;
				i--;
			}
			i += count_bs;
			if (!(line[i + 1]) && line[i] == '\\' && ((count_bs + 1) % 2))
				return (-1);
			if (!(count_bs % 2) && !(i = search_end_quote(line, i, quote)))
				return (quote);
		}
		i++;
	}
	return (0);
}
