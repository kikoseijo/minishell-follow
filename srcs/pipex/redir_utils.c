/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:19:04 by albaur            #+#    #+#             */
/*   Updated: 2022/07/19 09:22:09 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_del(t_stack **av)
{
	size_t	i;
	t_node	*node;
	t_node	*delenda;

	i = 0;
	while (av[i])
	{
		node = av[i]->top;
		while (node && node->next)
		{
			if (!ft_tokcmp(node->content, greater_than_type)
				|| !ft_tokcmp(node->content, smaller_than_type)
				|| !ft_tokcmp(node->content, d_greater_than_type))
//				|| !ft_tokcmp(node->content, d_smaller_than_type))
			{
				ft_printf(" 1 \n");
				ft_tokdisplay(node->content);
				delenda = node;
				node = node->next;
				ft_stackdelone(av[i], delenda, (void *)ft_tokdel);
				ft_tokdisplay(node->content);
				if (node)
				{
					ft_printf(" 2 \n");
					ft_tokdisplay(node->content);
					delenda = node;
					if (node->next)
						node = node->next;
					ft_stackdelone(av[i], delenda, (void *)ft_tokdel);
				}
				break ;
			}
			else
				node = node->next;
		}
		ft_stackiter(av[i], (void *)ft_tokdisplay);
		i++;
	}
}

void	redir_manager(t_stack **av, t_var *var, int mode, int type, int fd)
{
	t_node	*node;
	char	*path;

	node = (*av)->top;
	while (node)
	{
		if (!ft_tokcmp(node->content, type))
		{
			if (node->next)
				node = node->next;
			path = ft_lst_to_arrdup(node->content);
			var->fd[fd] = open(path, mode, 0644);
			if (var->fd[fd] < 0)
				ret_err(strerror(errno), NULL, 0);
			free(path);
			return ;
		}
		if (node->next)
			node = node->next;
	}
}

void	ft_redir_parser(t_stack **av, t_var *var)
{
	size_t	i;
	t_node	*node;

	i = 0;
	var->fd[0] = 0;
	var->fd[1] = 1;
	while (av[i])
	{
		node = av[i]->top;
		while (node && node->content)
		{
			if (!ft_tokcmp(node->content, greater_than_type))
				redir_manager(&av[i], var, O_WRONLY | O_CREAT,
					greater_than_type, 1);
			else if (!ft_tokcmp(node->content, smaller_than_type))
				redir_manager(&av[i], var, O_RDONLY,
					smaller_than_type, 0);
			else if (!ft_tokcmp(node->content, d_greater_than_type))
				redir_manager(&av[i], var, O_WRONLY | O_CREAT | O_APPEND,
					d_greater_than_type, 1);
//			else if (!ft_tokcmp(node->content, d_smaller_than_type))
//				ft_dst_manager(av, var);
			node = node->next;
		}
		i++;
	}
}
