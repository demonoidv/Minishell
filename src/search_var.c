/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 21:09:38 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/17 21:13:10 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_var(char ***env, char *name)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(name, env[i][0]))
			return (env[i][1]);
		i++;
	}
	return (NULL);
}
