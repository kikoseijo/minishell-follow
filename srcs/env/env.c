/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:46:40 by albaur            #+#    #+#             */
/*   Updated: 2022/06/27 17:58:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_read(char *path)
{
	t_read	r;

	if (!path)
		return (NULL);
	r.i = 1;
	r.tmp = malloc(sizeof(char) * 1);
	if (!r.tmp)
		return (NULL);
	r.tmp[0] = 0;
	r.fd = open(path, O_RDONLY, 0777);
	if (r.fd < 0)
	{
		close(r.fd);
		free(r.tmp);
		return (NULL);
	}
	while (r.i > 0)
	{
		r.i = read(r.fd, r.buffer, 1);
		if (r.i == -1)
		{
			close(r.fd);
			free(r.tmp);
			return (NULL);
		}
		r.buffer[r.i] = 0;
		r.tmp = ft_strjoin(r.tmp, r.buffer);
		if (!r.tmp)
		{
			close(r.fd);
			free(r.tmp);
			return (NULL);
		}
	}
	r.env = ft_split(r.tmp, '\n');
	close(r.fd);
	free(r.tmp);
	if (!r.env)
		return (NULL);
	return (r.env);
}

char	*env_get(char *str, char **env)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!str || !env)
		return (NULL);
	tmp = ft_strjoin(str, "=");
	if (!tmp)
	{
		free(tmp);
		return (NULL);
	}
	if (env_search(str, env))
	{
		i = env_search(str, env);
		tmp2 = ft_strdup(env[i] + ft_strlen(tmp));
		if (!tmp2)
		{
			free(tmp);
			free(tmp2);
			return (NULL);
		}
		return (tmp2);
	}
	free(tmp);
	free(tmp2);
	return (0);
}

char	**env_add(char *str, char ***env)
{
	size_t	i;
	char	**ptr;
	char	**new;

	i = 0;
	ptr = *env;
	new = malloc(sizeof(char *) * (ft_arrlen(ptr) + 2));
	if (!new)
		return (NULL);
	while (ptr[i])
	{
		new[i] = ptr[i];
		++i;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (NULL);
	new[i + 1] = 0;
	free(*env);
	return (new);
}

void	env_set(char *str, char *value, char ***env)
{
	size_t	i;
	char	*tmp;
	char	**ptr;

	ptr = *env;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return ;
	tmp = ft_strjoin(tmp, value);
	if (!tmp)
		return ;
	if (env_search(str, *env) >= 0)
	{
		i = env_search(str, *env);
		ptr[i] = tmp;
	}
	else
	{
		*env = env_add(tmp, env);
		if (!*env)
			return ;
	}
}

void	env_write(char *path, char **env)
{
	size_t	i;
	int		fd;

	i = 0;
	if (!path || !env || !*env)
		return ;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	while (env[i])
	{
		ft_putendl_fd(env[i], fd);
		++i;
	}
	close(fd);
}
