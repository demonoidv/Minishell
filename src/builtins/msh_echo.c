/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 21:16:40 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/07 21:30:13 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_echo(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		ft_putstr(arg[i]);
		i++;
		if (arg[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
