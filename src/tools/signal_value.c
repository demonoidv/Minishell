/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:12:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 15:54:39 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		signal_value(int sig)
{
	int			tmp;
	static int	signo = 0;

	tmp = 0;
	if (sig == -1)
		tmp = signo;
	else if (sig > -1)
		signo = sig;
	return (tmp);
}
