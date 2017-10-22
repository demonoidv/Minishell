/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_father.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 17:12:56 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 17:18:24 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_father(void)
{
	static pid_t	ppid = 0;

	if (!ppid)
		ppid = getppid();
	else if (ppid != getppid())
	{
		msh_error(TTY_ERR, "I/O error", DEFAULT);
		exit(1);
	}
}
