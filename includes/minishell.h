/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:47:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/27 00:26:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define CMD 1
# define DEFAULT 0
# define CHECK 1
# define SET 2
# define QUOTE '\''
# define DQUOTE '"'
# define DQUOTE_MOD 4
# define QUOTE_MOD 2
# define ESC_MOD 1

int		msh_error(int nbr, int mode);
int		event_manager(char **cmd, int pos, char *c);
void	wait_cmd(char ***env);
void	clean_line(char *cmd, int pos);
char	***get_env(char **environ);
char	**add_one_str(char **tab);
char	**line_to_tab(char *line);
char	*search_var(char ***env, char *name);
char	*del_char(char *cmd, int pos);
char	*del_frontchar(char *cmd, int pos);
char	check_escape(char *line);

#endif
