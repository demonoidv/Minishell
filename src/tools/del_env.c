/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:26:06 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/20 13:58:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(char ****env)
{
	int		i;
	char	***tmp;

	i = 0;
	tmp = *env;
	if (tmp && *tmp)
	{
		while (tmp && tmp[i])
		{
			ft_strdel(&(tmp[i][0]));
			ft_strdel(&(tmp[i][1]));
			ft_memdel((void**)&(tmp[i]));
			i++;
		}
		if (tmp)
			ft_memdel((void**)&tmp);
	}
	*env = NULL;
}
