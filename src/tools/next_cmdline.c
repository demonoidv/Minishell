/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 14:51:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_separator(char *cmdline, int *mode, char **dest)
{
	int			i;

	i = 0;
	while (cmdline[i] && (cmdline[i] != ';' || ((*mode) & 7)))
	{
		if (cmdline[i] == '\\' && !((*mode) & ESC_MOD))
			*mode = ((*mode) | ESC_MOD);
		else if (cmdline[i] == '"' && !((*mode) & (ESC_MOD | QUOTE_MOD)))
			*mode = (*mode) ^ DQUOTE_MOD;
		else if (cmdline[i] == '\'' && !((*mode) & (ESC_MOD | DQUOTE_MOD)))
			*mode = (*mode) ^ QUOTE_MOD;
		else if (((*mode) & ESC_MOD))
			*mode = ((*mode) ^ ESC_MOD);
		i++;
	}
	if (((*mode) & ESC_MOD))
		*mode = ((*mode) ^ ESC_MOD);
	if (i && dest)
		*dest = ft_strsub(cmdline, 0, i);
	return (i);
}

char		**next_cmdline(char *cmdline)
{
	int		i;
	int		j;
	int		mode;
	char	**multicmd;

	i = 0;
	j = 0;
	mode = 0;
	multicmd = NULL;
	while (cmdline[i])
	{
		while (cmdline[i] == ';' || cmdline[i] == ' ' || cmdline[i] == '\t' || \
		cmdline[i] == '\n' || (cmdline[i] == '\\' && cmdline[i + 1] == '\n'))
			i++;
		multicmd = add_one_str(multicmd, j + 1);
		i += search_separator(&(cmdline[i]), &mode, &(multicmd[j]));
		if (multicmd && multicmd[j])
			j++;
	}
	if (multicmd)
		multicmd[j] = NULL;
	return (multicmd);
}
