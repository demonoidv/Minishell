/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:12:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 15:15:13 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int		signal_value(int sig)
{
	int			tmp;
	static int	signo = 0;

	tmp = signo;
	signo = sig;
	return (tmp);
}
