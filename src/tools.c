/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:19:16 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 04:27:37 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	insert_char(char **str, int pos)
{
	int		oldpos;

	oldpos = pos;
	if (*str[pos])
	{
		
	}
}
*/

char	*del_char(char *cmd, int pos)
{
	char	*tmp;

	if (pos > 0)
	{
		tmp = ft_strdup(&cmd[pos]);
		cmd[pos - 1] = '\0';
		cmd = ft_strjoin_free(cmd, tmp, 3);
	}
	return (cmd);
}

void	clean_line(char *cmd, int pos)
{
	int		len;

	len = ft_strlen(cmd);
	while (pos++ < len)
		ft_putchar(127);
	while (--pos > 0)
	{
		ft_putchar(127);
		ft_putstr("\b\b");
	}
}

int		check_escape(char *line)
{
	int		i;
	int		count_bs;

	count_bs = 0;
	if (line)
	{
		i = ft_strlen(line);
		if (line[i])
		{
			while (i >= 0)
			{
				if (line[--i] == '\\')
					count_bs++;
			}
		}
	}
	return (count_bs % 2);
}

char	**ft_addstrtab(char ***tab, int more)
{
	int		i;
	char	**new;

	i = 0;
	while (*tab && (*tab)[i])
		i++;
	if ((new = (char**)malloc(sizeof(char*) * (more + i + 1))))
	{
		new[more + i] = NULL;
		if (i)
			while (--i >= 0)
				new[i] = (*tab)[i];
		ft_memdel((void**)tab);
	}
	return (new);
}

char	*ft_addchar(char **str, int more)
{
	int		i;
	char	*new;

	i = 0;
	if (*str)
		i = ft_strlen(*str);
	if ((new = (char*)malloc(sizeof(char) * more + i + 1)))
	{
		new[more + i] = '\0';
		new[more + i - 1] = '\0';
		if (i)
			while (--i >= 0)
				new[i] = *str[i];
		ft_strdel(str);
	}
	return (new);
}
