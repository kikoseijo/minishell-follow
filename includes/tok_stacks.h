/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_stacks.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:18:14 by faventur          #+#    #+#             */
/*   Updated: 2022/07/05 15:17:25 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_STACKS_H
# define TOK_STACKS_H

# include "minishell.h"
# include "stacks.h"
# include "ft_btree.h"

typedef struct s_token
{
	char	*str;
	int		type;
	int		subtype;
	size_t	index;
}				t_token;

// token types
enum e_lexer_type
{
	word_type = 1,
	empty_type,
	slash_type,
	tilde_type,
	greater_than_type = 10,
	d_greater_than_type,
	smaller_than_type,
	d_smaller_than_type,
	pipe_type = 20,
	and_type = 30,
	or_type
};

#endif