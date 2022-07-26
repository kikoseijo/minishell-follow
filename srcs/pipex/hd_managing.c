/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_managing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:53:59 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 15:23:50 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hd_performer(char *path, t_hd *hd)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);
	if (fd < 0)
	{
		ret_null("minishell:", strerror(errno));
		return ;
	}
	sig_toggle(3);
	while (42)
	{
		hd->buffer = readline("heredoc> ");
		if (!hd->buffer || (!ft_strcmp(hd->buffer, path)
				&& ft_strlen(hd->buffer) == ft_strlen(path)))
			break ;
		i = -1;
		while (hd->buffer[++i])
			ft_putchar_fd(hd->buffer[i], fd);
		ft_putchar_fd('\n', fd);
		free(hd->buffer);
	}
	free(hd->buffer);
	close(fd);
}

static void	hd_managing(char *path, t_var *var)
{
	t_hd	hd;

	hd.temp = malloc(sizeof(char) * 1);
	hd.temp[0] = '\0';
	ft_hd_performer(path, &hd);
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
