/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:19:16 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 02:22:15 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	get_cursor_pos(void)
{
	int				i;
	char			buff[10];
	unsigned long	pos;

	i = 0;
	pos = 0;
	ft_bzero(buff, 10);
	ft_putstr("\033[6n");
	if (read(0, buff, 2) != -1 && !ft_strcmp(buff, "\033["))
	{
		ft_bzero(buff, 10);
		while (read(0, &(buff[i]), 1) != -1 && buff[i] != 'R')
		{
			if (buff[i] == ';')
			{
				pos = (ft_atoi(buff) << 16);
				i = -1;
			}
			i++;
		}
		pos += ft_atoi(buff);
	}
	return (pos);
}

static int		search_end_quote(char *line, int pos, char quote)
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

char			check_escape(char *line)
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

char			**add_one_str(char **tab, int len)
{
	int		i;
	char	**new;

	i = 0;
	if ((new = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (tab && i < len)
		{
			new[i] = tab[i];
			i++;
		}
		new[i] = NULL;
		ft_memdel((void**)&(tab));
		tab = new;
	}
	return (tab);
}
