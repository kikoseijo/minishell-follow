/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:17:07 by albaur            #+#    #+#             */
/*   Updated: 2022/07/20 11:05:12 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_free(char ***env, char **tmp)
{
	ft_arr_freer(*env);
	if (*tmp)
		free(*tmp);
	return (0);
}

int	ft_exec_min(char *cmd)
{
	size_t	a;
	size_t	b;
	size_t	i;

	a = 0;
	b = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			++a;
		else if (cmd[i] == '.')
			++b;
		++i;
	}
	if (a == 0 && b == 0)
		return (0);
	else if (a > 0 && b > 0)
		return (1);
	else if (a > 0 && b == 0)
		return (2);
	else if (a == 0 && b > 0)
		return (3);
	return (4);
}

int	ft_exec_found(char **env, char **cmd_args, char *cmd, t_var *var)
{
	struct stat	stats;

	(void)var;
	if (stat(cmd_args[0], &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			return (3);
	}
	errno = 0;
	execve(cmd, cmd_args, env);
	ft_arr_freer(env);
	return (0);
}

int	ft_exec_not_found(char **env, char **cmd_args)
{
	if (ft_self_searcher(env, cmd_args))
		return (0);
	if (errno != 0)
	{
		if (ft_exec_min(cmd_args[0]) == 0)
			return (2);
		return (1);
	}
	ft_arr_freer(env);
	return (0);
}

int	ft_exec(char **cmd_args, t_var *var)
{
	int		i;
	char	*cmd;
	char	**env;

	i = 0;
	if (!cmd_args || !cmd_args[0])
		exit(0);
	if (tilde_searcher(cmd_args))
		tilde_replacer(cmd_args);
	i = builtin_launch(cmd_args);
	if (i != -99)
		exit(i);
	env = env_read(ENV_FILE);
	cmd = ft_path_searcher(cmd_args[0]);
	if (cmd)
		i = ft_exec_found(env, cmd_args, cmd, var);
	else
	{
		if (!access(cmd_args[0], X_OK) && ft_exec_min(cmd_args[0]) > 0)
			i = ft_exec_found(env, ft_exec_args(cmd_args), "/bin/bash", var);
		else
			i = ft_exec_not_found(env, cmd_args);
	}
	ft_exec_error(i, cmd_args);
	ft_exec_free(&env, &cmd);
	exit(i);
}
