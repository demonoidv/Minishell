/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 21:59:45 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 02:21:08 by vsporer          ###   ########.fr       */
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
			mode = (mode | ESC_MOD);
		else if (line[i] == '"' && !(mode & ESC_MOD) && !(mode & QUOTE_MOD))
			mode = mode ^ DQUOTE_MOD;
		else if (line[i] == '\'' && !(mode & ESC_MOD) && !(mode & DQUOTE_MOD))
			mode = mode ^ QUOTE_MOD;
		else if (line[i] != '\n' || (line[i] == '\n' && !(mode & ESC_MOD)))
		{
			if (line[i])
				*str = add_char(*str, &(line[i]));
			if (mode & ESC_MOD)
				mode = (mode ^ ESC_MOD);
		}
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
			tab = add_one_str(tab, j + 1);
			tab[j] = NULL;
			i += get_clean_str(&(line[i]), &(tab[j]));
			if (tab[j])
				j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
