/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:26:06 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/14 18:21:26 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(char ****env)
{
	int		i;
	char	***tmp;

	i = 0;
	tmp = *env;
	while (tmp && tmp[i])
	{
		ft_strdel(&(tmp[i][0]));
		ft_strdel(&(tmp[i][1]));
		i++;
	}
	if (*env && **env)
		ft_memdel((void**)env);
}
