/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:04:23 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 01:14:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_error(int nbr, char *from)
{
	if (from)
	{
		if (nbr == NO_FILE)
			ft_printf("%s: No such file or directory\n", from);
		else if (nbr == TM_ARGS)
			ft_printf("%s: too many arguments\n", from);
	}
	return (nbr);
}
