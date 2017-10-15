/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmdline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 14:27:44 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/15 14:36:32 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_cmdline(char **cmdline, int mode)
{
	char			*tmp;
	static char		**save = NULL;

	tmp = NULL;
	if (mode == SET)
		save = cmdline;
	else
		tmp = *save;
	return (tmp);
}
