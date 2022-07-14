/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_self_searcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:32:58 by albaur            #+#    #+#             */
/*   Updated: 2022/07/14 13:11:27 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_self_searcher(char **env, char **cmd_args)
{
	pid_t		pid;
	char		*args[3];
	char		*insidepwd;

	if (cmd_args[0][0] != '.')
		return (0);
	insidepwd = ft_strjoin(ft_strjoin(ft_getenv("PWD"), "/"), cmd_args[0]);
	args[0] = cmd_args[0];
	args[1] = insidepwd;
	args[2] = 0;
	if (!access(insidepwd, X_OK))
	{
		pid = fork();
		if (pid == 0)
			execve("/bin/bash", args, env);
		waitpid(pid, NULL, 0);
		ft_arr_freer(env);
		sig_toggle(0);
		return (1);
	}
	free(insidepwd);
	return (0);
}