/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:50:21 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/23 12:58:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_inlist(t_dlist **adlist, t_dlist *new)
{
	if ((*adlist)->prev && ((*adlist)->curr))
		*adlist = (*adlist)->prev;
	while ((*adlist)->next && !((*adlist)->next->curr))
		*adlist = (*adlist)->next;
	if ((*adlist)->next)
	{
		new->next = (*adlist)->next;
		new->next->prev = new;
	}
	(*adlist)->next = new;
	new->prev = (*adlist);
	*adlist = new;
	if ((*adlist)->next && (*adlist)->next->curr)
		*adlist = (*adlist)->next;
}

void			add_dlist(t_dlist **adlist, t_dlist *new)
{
	static int	first = 0;

	if (!(*adlist) && !first)
	{
		first = 1;
		*adlist = new;
		add_dlist(adlist, new_dlist(NULL));
		if (*adlist)
			(*adlist)->curr = 1;
	}
	else if (first && new)
		add_inlist(adlist, new);
}
