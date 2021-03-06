/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:00:14 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/21 20:43:37 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_value(int value, int mod)
{
	int			tmp;
	static int	ret;
	static int	ret_child;
	static int	ret_sig;

	if (mod == SET)
		ret = value;
	else if (mod == (SET | STATEXIT))
		ret_child = value;
	else if (mod == (SET | SIGEXIT))
	{
		ret_sig = value;
		ret_child = value + 128;
	}
	else if (mod == CHECK)
		return (ret);
	else if (mod == (CHECK | STATEXIT))
		return (ret_child);
	else if (mod == (CHECK | SIGEXIT))
	{
		tmp = ret_sig;
		ret_sig = -1;
		return (tmp);
	}
	return (0);
}
