/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_searcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:24:11 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 11:41:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path_searcher(char *cmd)
{
	t_searcher	s;

	s.i = -1;
	s.env_path = ft_getenv("PATH");
	s.paths = ft_split(s.env_path, ':');
	free(s.env_path);
	if (!s.paths)
		return (NULL);
	while (s.paths[++s.i])
	{
		s.append = ft_strjoin("/", cmd);
		s.exec_path = ft_strjoin(s.paths[s.i], s.append);
		if (!access(s.exec_path, R_OK) && ft_exec_min(cmd) != 1)
		{
			ft_arr_freer(s.paths);
			return (s.exec_path);
		}
		free(s.append);
		free(s.exec_path);
	}
	ft_arr_freer(s.paths);
	return (NULL);
}
