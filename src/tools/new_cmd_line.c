/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 14:23:25 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/22 14:25:50 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_cmd_line(char *cmd, unsigned long curs)
{
	clean_line(cmd, curs, DEFAULT);
	ft_putstr(cmd);
	ft_putstr("\v\r");
}
