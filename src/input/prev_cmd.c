/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 12:59:29 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/27 15:50:13 by vsporer          ###   ########.fr       */
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

void			prev_cmd(char **cmd, int mode)
{
	static int		nbcmd;
	static t_dlist	*dlist;

	if (*cmd && **cmd && mode == DEFAULT)
	{
		if (dlist && !ft_strcmp(dlist->cmd, *cmd))
			up_dlist(dlist);
		else
		{
			add_dlist(&dlist, new_dlist(*cmd));
			nbcmd++;
		}
	}
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
	if (nbcmd > CMD_MAX || mode == DEL_CMD)
	{
		del_cmd(&dlist, mode);
		nbcmd = mode == DEL_CMD ? 0 : nbcmd - 1;
	}
}
