/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_managing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:53:59 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 14:22:55 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ope_and_write(char **arr, char *path)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printerror("pipex", TMP_FILE);
		return (-1);
	}
	while (arr[i] && ft_strncmp(arr[i], path, ft_strlen(path))
		&& ft_strlen(arr[i]) - 1 != ft_strlen(path))
	{
		write(fd, arr[i], ft_strlen(arr[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (fd);
}

static char	*ft_add_backslash_en(char *line)
{
	char	*str;
	size_t	len;

	if (!line)
		return (NULL);
	if (line[0] != '\0')
	{
		len = ft_strlen(line);
		str = malloc(sizeof(char) * (len + 2));
		if (!str)
			return (NULL);
		ft_strcpy(str, line);
		str[len] = '\n';
		str[len + 1] = '\0';
	}
	else
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	free(line);
	return (str);
}

void	ft_hd_performer(char *path, t_hd *hd)
{
	while (42)
	{
		hd->buffer = readline("heredoc> ");
		if (!hd->buffer)
			return ;
		hd->buffer = ft_add_backslash_en(hd->buffer);
		if (!hd->buffer)
			return ;
		hd->cmp = ft_strncmp(hd->buffer, path,
				ft_strlen(hd->buffer) - 1);
		if (!hd->buffer || (!hd->cmp
				&& ft_strlen(hd->buffer) - 1 == ft_strlen(path)))
			break ;
		hd->temp = ft_concat(hd->temp, hd->buffer);
		if (!hd->temp)
			return ;
		free(hd->buffer);
	}
}

static void	hd_managing(char *path, t_var *var)
{
	t_hd	hd;

	hd.temp = malloc(sizeof(char) * 1);
	hd.temp[0] = '\0';
	ft_hd_performer(path, &hd);
	hd.arr = ft_split(hd.temp, '\n');
	if (!hd.arr)
	{
		free(hd.temp);
		return (ret_null("minishell:", strerror(errno)));
	}
	var->fd[0] = ope_and_write(hd.arr, path);
	ft_arr_freer(hd.arr);
	var->fd[0] = open(TMP_FILE, O_RDONLY);
	if (var->fd[0] < 0)
	{
		free(hd.temp);
		return (ret_null("minishell:", strerror(errno)));
	}
	free(hd.temp);
}

int	here_doc_redir_fd(t_stack **av, t_var *var)
{
	t_node	*node;
	char	*path;

	node = (*av)->top;
	while (node)
	{
		if (!ft_tokcmp(node->content, d_smaller_than_type))
		{
			if (node->next)
				node = node->next;
			else
				return (ret_err("minishell: parse error", NULL, 1));
			path = ft_lst_to_arrdup(node->content);
			hd_managing(path, var);
			if (var->fd[0] < 0)
				return (ret_err("minishell:", strerror(errno), 1));
			node_del(node->prev, av);
			node_del(node, av);
			free(path);
			return (0);
		}
		if (node->next)
			node = node->next;
	}
	return (1);
}
