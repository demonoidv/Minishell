/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cmdtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:17:15 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/11 20:41:02 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmdtab(char ***cmdtab)
{
	int		i;

	i = 0;
	while (cmdtab && *cmdtab && (*cmdtab)[i])
	{
		ft_strdel(&((*cmdtab)[i]));
		i++;
	}
	ft_memdel((void**)cmdtab);
}
