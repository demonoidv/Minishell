/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 12:22:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/23 12:58:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist		*new_dlist(const char *cmd)
{
	t_dlist		*new;

	if ((new = (t_dlist*)malloc(sizeof(t_dlist))))
	{
		new->cmd = ft_strdup(cmd);
		new->curr = 0;
		new->prev = NULL;
		new->next = NULL;
	}
	return (new);
}

void		del_dlist(t_dlist **todel)
{
	if (*todel)
	{
		ft_strdel(&((*todel)->cmd));
		if ((*todel)->next)
			(*todel)->next->prev = (*todel)->prev;
		if ((*todel)->prev)
			(*todel)->prev->next = (*todel)->next;
		(*todel)->prev = NULL;
		(*todel)->next = NULL;
		ft_memdel((void**)todel);
	}
}

void		add_current(t_dlist **dlist, char **current)
{
	t_dlist		*tmp;

	tmp = *dlist;
	if (tmp && tmp->cmd && ft_strcmp(tmp->cmd, *current))
	{
		while (tmp->next && !(tmp->curr))
			tmp = tmp->next;
		ft_strdel(&(tmp->cmd));
		tmp->cmd = ft_strdup(*current);
	}
	ft_strdel(current);
}

void		up_dlist(t_dlist **toup)
{
	t_dlist		*tmp;

	tmp = *toup;
	if (tmp->next && !(tmp->next->curr))
	{
		if (tmp->prev && !(tmp->curr))
			tmp = tmp->prev;
		while (tmp->next && !(tmp->next->curr))
			tmp = tmp->next;
		if ((*toup)->next)
			(*toup)->next->prev = (*toup)->prev;
		if ((*toup)->prev)
			(*toup)->prev->next = (*toup)->next;
		(*toup)->next = tmp->next;
		if ((*toup)->next)
			(*toup)->next->prev = *toup;
		tmp->next = *toup;
		(*toup)->prev = tmp;
		if ((*toup)->next && (*toup)->next->curr)
		{
			*toup = (*toup)->next;
			ft_strdel(&((*toup)->cmd));
		}
	}
}
