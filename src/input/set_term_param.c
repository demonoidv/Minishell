/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:02:30 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/16 23:12:34 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	set_term_param(int mode)
{
	struct termios			term;
	static struct termios	save;

	if (mode == CMD && !tcgetattr(0, &term))
	{
		save = term;
		if (term.c_lflag & ECHO)
			term.c_lflag = term.c_lflag ^ ECHO;
		if (term.c_lflag & ICANON)
			term.c_lflag = term.c_lflag ^ ICANON;
		term.c_cc[VMIN] = 0;
		term.c_cc[VTIME] = 1;
	}
	else if (mode == DEFAULT)
		term = save;
	tcsetattr(0, TCSANOW, &term);
}
