/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 15:12:04 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 21:10:53 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static int	count_line(char *cmd, int pos_y, int pos_x, int savenl)
{
	int				i;
	int				nl;
	struct winsize	size;

	i = 0;
	nl = 0;
	ioctl(0, TIOCGSIZE, &size);
	while (cmd[i])
	{
		if (cmd[i] == '\n' || (pos_y) > size.ws_col)
		{
			nl++;
			pos_y = 0;
		}
		pos_y++;
		i++;
	}
	nl = (pos_x + nl) - size.ws_row;
	if (nl > 0)
		savenl += nl;
	return (savenl);
}

void		clean_line(char *cmd, unsigned long pos, int mode)
{
	int				y;
	int				x;
	static int		savenl;

	x = CURSOR_X(pos);
	y = CURSOR_Y(pos);
	if (cmd && (!mode || mode == 2))
	{
		savenl = count_line(cmd, y, x - savenl, savenl);
		ft_printf("\033[%d;%dH", x - savenl, y);
		if (!mode)
		{
			ft_putstr("\033[J");
			ft_putstr("\033[K");
		}
	}
	else if (mode == 1)
		savenl = 0;
}
