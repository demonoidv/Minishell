/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:46:28 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/14 22:19:55 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **envp)
{
	char	***env;

	av = NULL;
	if (ac != 1)
		return (1);
	exit_value(-1, SET);
	env = get_env(envp);
	env = wait_cmd(env);
	del_env(&env);
	return (exit_value(0, CHECK));
}
