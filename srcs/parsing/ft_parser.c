/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:01:06 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 14:20:49 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ret_parse_err(t_token *token)
{
	if (token && token->str)
		ft_printf("minishell: syntax error near unexpected token '%s'\n",
			token->str);
	return (258);
}

int	ft_parser_pt2(t_node *node)
{
	if (!ft_tokcmp(node->content, and_type)
		|| !ft_tokcmp(node->content, or_type))
		return (1);
	else if ((!ft_tokcmp(node->content, greater_than_type)
			|| !ft_tokcmp(node->content, smaller_than_type)
			|| !ft_tokcmp(node->content, d_greater_than_type)
			|| !ft_tokcmp(node->content, d_smaller_than_type))
		&& (!node->next
			|| !ft_tokcmp(node->next->content, greater_than_type)
			|| !ft_tokcmp(node->next->content, smaller_than_type)
			|| !ft_tokcmp(node->next->content, d_greater_than_type)
			|| !ft_tokcmp(node->next->content, d_smaller_than_type)))
		return (1);
	else if (!ft_tokcmp(node->content, pipe_type) && (!node->next
			|| !ft_tokcmp(node->next->content, pipe_type)
			|| !ft_tokcmp(node->next->content, and_type)))
		return (1);
	return (0);
}

int	ft_parser(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	if (!ft_tokcmp(current->content, pipe_type))
		return (ret_parse_err(current->content));
	while (current)
	{
		if (ft_parser_pt2(current))
			return (ret_parse_err(current->content));
		current = current->next;
	}
	return (0);
}
