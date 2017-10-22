/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_one_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 14:32:31 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 14:33:19 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_one_str(char **tab, int len)
{
	int		i;
	char	**new;

	i = 0;
	if ((new = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (tab && i < len)
		{
			new[i] = tab[i];
			i++;
		}
		if (!tab)
			new[1] = NULL;
		new[i] = NULL;
		ft_memdel((void**)&(tab));
		tab = new;
	}
	return (tab);
}
