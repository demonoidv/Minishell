/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:02:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 15:28:13 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	signal_handler(int sig)
{
	pid_t	last;

	last = last_pid(0);
	signal_value(sig);
	if (last > 0)
	{
		if (sig == SIGINT && last)
			kill(last, SIGINT);
	}
}
