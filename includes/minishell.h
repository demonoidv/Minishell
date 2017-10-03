/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:47:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/03 02:10:40 by vsporer          ###   ########.fr       */
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
# define CMD_MAX 50
# define PREV_CMD 1
# define NEXT_CMD 2
# define DEL_CMD 3
# define NO_HISTORY 32768
# define CURSOR_X(n) n >> 16
# define CURSOR_Y(n) n & 255
/*
**	ERROR CODE
*/
# define NO_FILE 1
# define TM_ARGS 2

typedef struct		s_dlist
{
	int				curr;
	char			*cmd;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

/*
**	CORE FUNCTION
*/
int				msh_error(int nbr, char *from);
void			msh_switch(char **cmdtab);
char			***get_env(char **environ);
char			*search_var(char ***env, char *name);
/*
**	INPUT FUNCTION
*/
int				event_manager(char **cmd, int pos, char *c, unsigned long curs);
void			clean_line(char *cmd, unsigned long pos, int mode);
void			wait_cmd(char ***env);
void			prev_cmd(char **cmd, int mode);
void			set_term_param(int mode);
void			add_dlist(t_dlist **adlist, t_dlist *new);
void			add_current(t_dlist **dlist, char **cmd);
void			del_dlist(t_dlist **todel);
void			up_dlist(t_dlist **toup);
char			**add_one_str(char **tab, int len);
char			**line_to_tab(char *line);
char			*del_char(char *cmd, int pos, unsigned long curs);
char			*del_frontchar(char *cmd, int pos, unsigned long curs);
char			check_escape(char *line);
t_dlist			*new_dlist(const char *cmd);
unsigned long	get_cursor_pos(void);
/*
**	BUILTINS FUNCTION
*/
void			msh_exit(char **arg);

#endif
