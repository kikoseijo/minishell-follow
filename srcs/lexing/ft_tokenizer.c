/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:59:09 by faventur          #+#    #+#             */
/*   Updated: 2022/07/26 14:19:28 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The tokenizer() function creates a stack with every element of the
** string array passed as a parameter, that is transformed into a
** structure composed of a string and a type (what is called "process
** of tokenization") by the ft_token_creator() function. Afterwards,
** it calls the ms_dollar_manager() function which searches each
** element of the stack for environment variable names to be
** replaced, before calling the ms_dollar_quote_eraser() function
** that rewrite each string without quotes.
** The stack is then sent to the pipe_manager() function, in charge
** of executing the commands.
*/

t_node	*token_parser(t_stack *stack, int type)
{
	t_node	*current;

	current = stack->top;
	while (current->next)
	{
		if (ft_tokcmp(current->content, type))
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	ft_token_creator_pt2(t_token *token, char *line)
{
	if (!ft_strnstrbool(line, "<", 1))
		token->type = smaller_than_type;
	else if (!ft_strnstrbool(line, ">>", 2))
		token->type = d_greater_than_type;
	else if (!ft_strnstrbool(line, ">", 1))
		token->type = greater_than_type;
	else if (line[0] == '\0')
		token->type = empty_type;
	else
		token->type = word_type;
}

t_token	*ft_token_creator(char *line, size_t line_index)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(*token));
	token->str = ft_strdup(line);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->index = line_index;
	if (!ft_strnstrbool(line, "&&", 2))
		token->type = and_type;
	else if (!ft_strnstrbool(line, "||", 2))
		token->type = or_type;
	else if (!ft_strnstrbool(line, "|", 1))
		token->type = pipe_type;
	else if (!ft_strnstrbool(line, "<<", 2))
		token->type = d_smaller_than_type;
	else
		ft_token_creator_pt2(token, line);
	return (token);
}

void	ft_tokenizer(char **arr)
{
	t_stack	*new;
	t_token	*token;
	t_node	*node;
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	new = ft_stacknew();
	while (arr[i])
	{
		token = ft_token_creator(arr[i], i);
		node = ft_newnode(token);
		ft_stackadd_bottom(new, node);
		i++;
	}
	if (!ft_parser(new))
	{
		ms_dollar_manager(new);
		ms_dollar_quote_eraser(new);
		ft_arr_freer(arr);
		pipe_manager(new);
	}
}
