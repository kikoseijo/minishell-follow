/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:12:55 by albaur            #+#    #+#             */
/*   Updated: 2022/07/26 13:37:21 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

static void	clear_gt0(t_node *top)
{
	t_token	*token;

	if (top->next)
	{
		top->prev->next = top->next;
		top->next->prev = top->prev;
	}
	else
		top->prev->next = NULL;
	token = top->content;
	free(token->str);
	token->str = NULL;
	free(token);
	token = NULL;
	free(top);
	top = NULL;
}

static void	clear_eq0(t_stack **av, t_node *top)
{
	t_token	*token;

	token = top->content;
	if (top->next)
	{
		top->next->prev = NULL;
		(*av)->top = top->next;
	}
	else
		(*av)->top = NULL;
	free(token->str);
	token->str = NULL;
	free(token);
	token = NULL;
	free(top);
	top = NULL;
}

void	node_del(t_node *node, t_stack **av)
{
	int		i;
	t_node	*top;

	i = -1;
	top = (*av)->top;
	while (top)
	{
		++i;
		if (top == node)
			break ;
		top = top->next;
	}
	if (i == -1 || !top)
	{
		ft_printf("node_del: error: couldn't find node");
		return ;
	}
	else if (i == 0)
		clear_eq0(av, top);
	else if (i > 0)
		clear_gt0(top);
}
