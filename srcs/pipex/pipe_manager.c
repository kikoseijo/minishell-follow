/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 21:43:57 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 11:48:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manager_exit(t_var *var, t_stack **arr)
{
	ft_intarr_freer(var->pipes);
	ft_stacktab_clear(arr);
}

static void	init_fd(t_var *var)
{
	var->fd[0] = 0;
	var->fd[1] = 1;
}

int	pipe_manager(t_stack *stack)
{
	t_stack	**arr;
	t_var	var;
	size_t	j;

	j = -1;
	init_fd(&var);
	arr = ft_stack_splitter(stack);
	var.stack_len = ft_stacktablen(arr);
	pipex_pipes(var.stack_len, &var);
	while (arr[++j])
	{
		init_fd(&var);
		if (ft_redir_parser(arr[j], &var) == 1)
			break ;
		if (pipex_open(arr, j, &var) || child_process(arr, j, &var))
		{
			manager_exit(&var, arr);
			return (1);
		}
		pipex_close(arr, j, &var);
	}
	manager_exit(&var, arr);
	return (0);
}
