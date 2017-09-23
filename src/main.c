/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:46:28 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/22 21:12:33 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **envp)
{
	char	***env;

	av = NULL;
	if (ac != 1)
		return (1);
	env = get_env(envp);
	wait_cmd(env);
	return (0);
}
