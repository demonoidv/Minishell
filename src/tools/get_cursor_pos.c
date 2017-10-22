/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 14:31:16 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 14:33:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	get_cursor_pos(void)
{
	int				i;
	char			buff[10];
	unsigned long	pos;

	i = 0;
	pos = 0;
	ft_bzero(buff, 10);
	ft_putstr("\033[6n");
	if (read(0, buff, 2) != -1 && !ft_strcmp(buff, "\033["))
	{
		ft_bzero(buff, 10);
		while (read(0, &(buff[i]), 1) != -1 && buff[i] != 'R')
		{
			if (buff[i] == ';')
			{
				pos = (ft_atoi(buff) << 16);
				i = -1;
			}
			i++;
		}
		pos += ft_atoi(buff);
	}
	return (pos);
}
