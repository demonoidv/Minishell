/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 23:17:18 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/11 20:21:44 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		next_cmdline(char ***cmdtab)
{
	int				i;
	static int		pos;
	static char		**save;

	i = 0;
	if (pos > 0)
	{
		pos--;
		*cmdtab = &((*cmdtab)[pos]);
		if ((*cmdtab)[1])
			**cmdtab = ft_strdup("\033;");
		(*cmdtab)++;
	}
	else
		save = *cmdtab;
	if (!(**cmdtab) || exit_value(0, CHECK) >= 0)
	{
		pos = 0;
		*cmdtab = save;
		return (0);
	}
	while ((*cmdtab)[i + 1] && ft_strcmp((*cmdtab)[i], "\033;"))
		i++;
	if (!ft_strcmp((*cmdtab)[i], "\033;") && (*cmdtab)[pos])
		ft_strdel((*cmdtab) + i);
	pos = i + 1;
	return (1);
}
