/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:48:05 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/05 16:49:10 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_var(char ***env)
{
	int		i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}
