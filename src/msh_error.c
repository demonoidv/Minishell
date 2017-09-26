/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/26 17:09:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_error(int nbr, int mode)
{
	static int	errnb;

	if (mode == SET)
		errnb = nbr;
	return (errnb);
}
