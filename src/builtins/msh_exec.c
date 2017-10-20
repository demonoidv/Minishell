/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:24:40 by vsporer           #+#    #+#             */
/*   Updated: 2017/10/20 20:07:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static int		check_directory(char *arg)
{
	int				ret;
	struct stat		st;

	ret = NO_FILE;
	arg[ft_strlen(arg) - 1] = '\0';
	if (!stat(arg, &st))
	{
		if (S_ISDIR(st.st_mode))
			ret = IS_DIR;
		else
			ret = NO_DIR;
	}
	arg[ft_strlen(arg)] = '/';
	return (ret);
}

static char		**join_env_var(char ***env)
{
	int		i;
	int		len;
	char	**envp;

	i = 0;
	if (!env || (env && !(*env)))
		return (NULL);
	len = count_var(env);
	if ((envp = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (env[i])
		{
			envp[i] = ft_strjoin_free(ft_strjoin(env[i][0], "="), env[i][1], 1);
			i++;
		}
		envp[i] = NULL;
	}
	return (envp);
}

static int		exec_prog(char *path, char **args, char ***env)
{
	int		i;
	int		status;
	char	**envp;
	pid_t	pid;

	i = 0;
	envp = join_env_var(env);
	if ((pid = fork()) > 0 && waitpid(pid, &status, WUNTRACED) == pid)
	{
		last_pid(pid);
		while (envp && envp[i])
			ft_strdel(&(envp[i++]));
		ft_memdel((void**)&envp);
		ft_strdel(&path);
		if (WIFEXITED(status))
			exit_value(WEXITSTATUS(status), (SET | STATEXIT));
		if (WIFSIGNALED(status))
			exit_value(WTERMSIG(status), (SET | SIGEXIT));
		if (WIFSTOPPED(status))
			kill(pid, SIGKILL);
		if (WIFSIGNALED(status))
			return (SIG_TERM);
	}
	else if (!pid && execve(path, args, envp) == -1)
		return (EXC_FORM);
	else if (pid == -1)
		return (FORK_ERR);
	return (0);
}

static int		search_path(char **bin, char *name, char *path)
{
	int		i;
	char	**pathtab;

	i = 0;
	if (path)
	{
		pathtab = ft_strsplit(path, ':');
		while (pathtab && pathtab[i])
		{
			if (pathtab[i][ft_strlen(pathtab[i]) - 1] != '/')
				pathtab[i] = ft_strjoin_free(pathtab[i], "/", 1);
			*bin = ft_strjoin_free(pathtab[i], name, 1);
			if (!access(*bin, F_OK) && !access(*bin, X_OK))
			{
				while (pathtab[++i])
					ft_strdel(&(pathtab[i]));
				ft_memdel((void**)&pathtab);
				return (0);
			}
			ft_strdel(bin);
			i++;
		}
		ft_memdel((void**)&pathtab);
	}
	return (NO_CMD);
}

int				msh_exec(char **arg, char ***env, char ***envp)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if ((tmp = ft_strchr(arg[0], '/')))
	{
		if ((tmp[ft_strlen(tmp) - 1]) == '/')
			ret = check_directory(arg[0]);
		else if (access(arg[0], F_OK) == -1)
			ret = NO_FILE;
		else if (access(arg[0], X_OK) == -1)
			ret = PERM_DEN;
		else
			ret = exec_prog(ft_strdup(arg[0]), arg, envp);
		if (!(*tmp))
			*tmp = '/';
		return (ret);
	}
	else if (!(ret = search_path(&tmp, arg[0], search_var(env, "PATH"))))
		return (exec_prog(tmp, arg, envp));
	else
		return (ret);
}
