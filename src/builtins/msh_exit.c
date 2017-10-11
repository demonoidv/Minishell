/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:52:11 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/11 15:21:11 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		msh_exit(char **arg)
{
	char	ret;

	ret = 0;
	if (msh_tablen(arg) > 1)
		msh_error(TM_ARGS, "exit", EXI_ERR);
	else if (arg[0])
		exit_value((unsigned char)ft_atoi(arg[0]), SET);
	else
		exit_value(0, SET);
}
