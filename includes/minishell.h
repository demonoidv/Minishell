/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:47:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/25 04:28:03 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define CMD 1
# define DEFAULT 0

int		check_escape(char *line);
int		event_manager(char **cmd, int pos);
void	wait_cmd(char ***env);
void	clean_line(char *cmd, int pos);
char	***get_env(char **environ);
char	**get_quote(char **cmd, int pos, char quote);
char	**ft_addstrtab(char ***tab, int more);
char	*ft_addchar(char **str, int more);
char	*search_var(char ***env, char *name);
char	*del_char(char *cmd, int pos);

#endif
