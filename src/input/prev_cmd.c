/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 12:59:29 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/29 14:40:11 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		del_cmd(t_dlist **dlist, int mode)
{
	t_dlist		*tmp;

	tmp = *dlist;
	while (tmp->prev)
		tmp = tmp->prev;
	if (mode == DEL_CMD)
	{
		while (*dlist)
		{
			*dlist = tmp->next;
			del_dlist(&tmp);
			tmp = *dlist;
		}
	}
	else
		del_dlist(&tmp);
}

static void		add_cmd(t_dlist **dlist, char *cmd, int mode)
{
	static int	nbcmd;

	if (cmd && *cmd && mode == DEFAULT)
	{
		if (*dlist && (*dlist)->cmd && !ft_strcmp((*dlist)->cmd, cmd))
			up_dlist(dlist);
		else
		{
			add_dlist(dlist, new_dlist(cmd));
			nbcmd++;
		}
	}
	if (nbcmd > CMD_MAX || mode == DEL_CMD)
	{
		del_cmd(dlist, mode);
		nbcmd = mode == DEL_CMD ? 0 : nbcmd - 1;
	}
}

void			prev_cmd(char **cmd, int mode)
{
	static t_dlist	*dlist;

	if (mode == DEFAULT || mode == DEL_CMD)
		add_cmd(&dlist, *cmd, mode);
	else if (dlist && mode == PREV_CMD)
	{
		if (dlist->prev)
			dlist = dlist->prev;
		*cmd = ft_strdup(dlist->cmd);
	}
	else if (dlist && mode == NEXT_CMD)
	{
		if (dlist->next)
			dlist = dlist->next;
		*cmd = ft_strdup(dlist->cmd);
	}
}
