/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 21:59:45 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 02:50:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*add_char(char *str, char *c, int *mode)
{
	int		len;
	char	tmp;

	len = str ? ft_strlen(str) : 0;
	if (*c != '\n' || (*c == '\n' && !((*mode) & ESC_MOD)))
	{
		if (*c)
		{
			tmp = c[1];
			c[1] = '\0';
			str = ft_strjoin_free(str, c, 1);
			c[1] = tmp;
			if (str && ((*mode) & ESC_MOD) && ((*mode) & 6) && \
			(str[len] == 'n' || str[len] == 't'))
				str[len] = str[len] == 'n' ? '\n' : '\t';
		}
		if ((*mode) & ESC_MOD)
			*mode = ((*mode) ^ ESC_MOD);
	}
	return (str);
}

static int		var_to_value(char **str, char *line, int *mode, char ***env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (line[i] == '~' && !((*mode) & 7))
		*str = ft_strjoin_free(*str, search_var(env, "HOME"), 1);
	else if (line[i] == '~')
		*str = ft_strjoin_free(*str, "~", 1);
	else if (line[i] == '$' && !((*mode) & 3) && line[i + 1])
	{
		while (line[i + 1] && ft_isalpha(line[i + 1]))
			i++;
		if (i > 0)
		{
			tmp = ft_strsub(line, 1, i);
			*str = ft_strjoin_free(*str, search_var(env, tmp), 1);
			ft_strdel(&tmp);
		}
		else if (line[++i] == '?')
			*str = ft_strjoin_free(*str, ft_itoa(exit_value(0, 9)), 3);
	}
	else
		*str = ft_strjoin_free(*str, "$", 1);
	return (i);
}

static int		get_clean_str(char *line, char **str, char ***env)
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
		else if ((line[i] == '~' || line[i] == '$') && !(mode & ESC_MOD))
			i += var_to_value(str, &(line[i]), &mode, env);
		else if (str)
			*str = add_char(*str, &(line[i]), &mode);
		i++;
	}
	return (i - 1);
}

char			**line_to_tab(char *line, char ***env)
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
			i += get_clean_str(&(line[i]), &(tab[j]), env);
			if (tab && tab[j])
				j++;
		}
		i++;
	}
	if (tab)
		tab[j] = NULL;
	return (tab);
}
