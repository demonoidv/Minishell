/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 12:22:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/27 16:00:44 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist		*new_dlist(const char *cmd)
{
	t_dlist		*new;

	if ((new = (t_dlist*)malloc(sizeof(t_dlist))))
	{
		new->cmd = ft_strdup(cmd);
		new->prev = NULL;
		new->next = NULL;
	}
	return (new);
}

void		add_dlist(t_dlist **adlist, t_dlist *new)
{
	if (!(*adlist))
		*adlist = new;
	else if (new)
	{
		if ((*adlist)->next)
		{
			new->next = (*adlist)->next;
			(*adlist)->next->prev = new;
		}
		(*adlist)->next = new;
		new->prev = (*adlist);
		*adlist = new;
	}
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

void		up_dlist(t_dlist *toup)
{
	t_dlist		*tmp;

	tmp = toup;
	while (tmp->next)
		tmp = tmp->next;
	if (toup->next)
		toup->next->prev = toup->prev;
	if (toup->prev)
		toup->prev->next = toup->next;
	tmp->next = toup;
	toup->prev = tmp;
	toup->next = NULL;
}
