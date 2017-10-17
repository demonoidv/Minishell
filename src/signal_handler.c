/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:02:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/16 23:37:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	signal_handler(int sig)
{
	pid_t	last;

	last = last_pid(0);
	signal_value(sig);
	if (sig == SIGHUP)
	{
		ft_putchar('\n');
		exit(1);
	}
}
