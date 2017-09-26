/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 21:59:45 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/27 00:50:03 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*add_char(char *str, char *c)
{
	char	tmp;

	tmp = c[1];
	c[1] = '\0';
	str = ft_strjoin_free(str, c, 1);
	c[1] = tmp;
	return (str);
}

static int		get_clean_str(char *line, char **str)
{
	int		i;
	int		mode;

	i = 0;
	mode = 0;
	while (line[i] && ((line[i] != ' ' && line[i] != '\t') || (mode & 6)))
	{
		if (line[i] == '\\' && !(mode & ESC_MOD))
			mode = (mode & ESC_MOD);
		else if (line[i] == '\\')
		{
			*str = add_char(*str, &(line[i]));
			mode = (mode ^ ESC_MOD);
		}
		else if (line[i] == '"' && !(mode & ESC_MOD) && !(mode & QUOTE_MOD))
			mode = mode ^ DQUOTE_MOD;
		else if (line[i] == '\'' && !(mode & ESC_MOD) && !(mode & DQUOTE_MOD))
			mode = mode ^ QUOTE_MOD;
		else if (line[i] != '\n' || (line[i] == '\n' && !(mode & ESC_MOD)))
			*str = add_char(*str, &(line[i]));
		i++;
	}
	return (i - 1);
}

char			**line_to_tab(char *line)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = NULL;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			tab = add_one_str(tab);
			i = get_clean_str(&(line[i]), &(tab[j]));
			j++;
		}
		i++;
	}
	return (tab);
}
