/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:24:40 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/21 19:42:54 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_directory(char *arg)
{
	int				ret;
	char			*tmp;
	struct stat		st;

	ret = NO_FILE;
	tmp = ft_strdup(arg);
	if (tmp && tmp[ft_strlen(tmp) - 1] == '/')
		tmp[ft_strlen(tmp) - 1] = '\0';
	if (!stat(tmp, &st))
	{
		if (S_ISDIR(st.st_mode))
			ret = IS_DIR;
		else
			ret = NO_DIR;
	}
	ft_strdel(&tmp);
	return (ret);
}
