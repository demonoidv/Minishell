/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 12:43:09 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/16 18:00:46 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	msh_signal(void)
{
	int		i;

	i = 1;
	while (i < 30)
	{
		if (i != 9 && i != 17)
			signal(i, &signal_handler);
		i++;
	}
}
