/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 17:19:16 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 18:35:15 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_line(char *cmd, int pos)
{
	int		len;

	len = ft_strlen(cmd);
	while (pos <= len)
	{
		ft_putchar(127);
		pos++;
	}
	while (pos > 0)
	{
		ft_putchar('\b');
		ft_putchar(127);
		ft_putchar('\b');
		pos--;
	}
}
/*
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
*/
char	check_escape(char *line)
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
