/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 14:13:45 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/16 17:23:55 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	last_pid(pid_t pid)
{
	pid_t			tmp;
	static pid_t	last = 0;

	tmp = last;
	last = pid;
	return (tmp);
}
