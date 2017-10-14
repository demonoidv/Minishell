/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 15:53:31 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/14 23:42:57 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			var_to_value(char **arg, char ***env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arg && arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '~' && j > 0 && arg[i][j - 1] == '\\')
				
			else 
			j++;
		}
		i++;
	}
}
