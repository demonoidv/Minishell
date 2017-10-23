/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:47:07 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/23 13:14:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define CMD 1
# define DEFAULT 0
# define CHECK 1
# define SET 2
# define SIGEXIT 4
# define STATEXIT 8
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
# define ENV_ERR 1
# define CD_ERR 2
# define EXI_ERR 3
# define SENV_ERR 4
# define NO_FILE 1
# define TM_ARGS 2
# define NO_CMD 3
# define STX_ERR 4
# define VAR_NSET 5
# define PERM_DEN 6
# define NO_DIR 7
# define IS_DIR 8
# define EXC_FORM 9
# define FORK_ERR 10
# define TTY_ERR 11
# define SIG_TERM 12

typedef struct		s_dlist
{
	int				curr;
	char			*cmd;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;
/*
**	TOOLS
*/
int					count_var(char ***env);
int					msh_tablen(char **tab);
int					exit_value(int value, int mod);
int					signal_value(int sig);
int					check_directory(char *arg);
void				del_cmdtab(char ***cmdtab);
void				del_env(char ****env);
void				check_father(void);
char				check_escape(char *line);
char				*search_var(char ***env, char *name);
char				*save_cmdline(char **cmdline, int mode);
char				*new_cmd_line(char *cmd, unsigned long curs);
char				**next_cmdline(char *cmdline);
char				**add_one_str(char **tab, int len);
pid_t				last_pid(pid_t pid);
unsigned long		get_cursor_pos(void);
/*
**	CORE FUNCTION
*/
int					msh_switch(char **cmdtab, char ****env);
void				msh_error(int nbr, char *from, int funcnum);
void				msh_signal(void);
char				***get_env(char **environ);
void				signal_handler(int sig);
/*
**	INPUT FUNCTION
*/
int					event_manager(char **cmd, int pos, char *c, \
					unsigned long curs);
void				clean_line(char *cmd, unsigned long pos, int mode);
void				prev_cmd(char **cmd, int mode);
void				set_term_param(int mode);
void				add_dlist(t_dlist **adlist, t_dlist *new);
void				add_current(t_dlist **dlist, char **cmd);
void				del_dlist(t_dlist **todel);
void				up_dlist(t_dlist **toup);
void				wait_cmd(char ****env);
char				**line_to_tab(char *line, char ***env);
char				*del_char(char *cmd, int pos, unsigned long curs);
char				*del_frontchar(char *cmd, int pos, unsigned long curs);
t_dlist				*new_dlist(const char *cmd);
/*
**	BUILTINS FUNCTION
*/
int					msh_exec(char **arg, char ***env, char ***envp);
void				msh_exit(char **arg);
void				msh_cd(char **arg, char ****env);
void				msh_echo(char **arg);
void				msh_env(char **arg, char ***env, char ***envp);
void				msh_setenv(char **arg, char ****env);
void				msh_unsetenv(char **arg, char ****env);
void				edit_env(char *arg, char ****env);

#endif
