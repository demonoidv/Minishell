/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:23:56 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 17:08:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_line(char *cmd, int pos)
{
	int		len;

	if (cmd)
	{
		clean_line(cmd, pos);
		ft_putstr(cmd);
		len = ft_strlen(cmd);
		while (len >= pos)
		{
			ft_putchar('\b');
			len--;
		}
	}
}
