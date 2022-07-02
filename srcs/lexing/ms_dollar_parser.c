/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:16:18 by faventur          #+#    #+#             */
/*   Updated: 2022/07/02 18:45:09 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The dquote_dollar_counter() function counts the amount of characters
 * of the name of the environment variable preceded by the dollar ($)
 * symbol in the string passed as a parameter.
 * 
 * The dquote_dollar_parser() function allocates (with malloc(3)) and
 * returns a "fresh" null-terminated string representing the the name
 * of the environment variable found in the string passed as a
 * parameter.
 * 
 * The dquote_dollar_replacer() function checks if the environment
 * variable name passed as a parameter corresponds to an existant
 * variable and, if it's the case, replaces it with its content
 * in the new string.
*/

#include "minishell.h"

static void	ms_dollar_measurer(t_dollar *dollar)
{
	dollar->var_len = ft_strlen(dollar->var);
	dollar->len = ft_strlen(dollar->line) - (dollar->varname_len + 1)
		+ dollar->var_len;
}

static void	ms_dollar_tailor(t_dollar *dollar)
{
	dollar->i = 0;
	dollar->j = 0;
	ms_dollar_measurer(dollar);
	dollar->str = malloc(sizeof(char) * (dollar->len + 1));
	if (!dollar->str)
		return ;
	while (dollar->line[dollar->i] && dollar->line[dollar->i] != '$')
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	if (dollar->line[dollar->i] == '$')
		dollar->str[dollar->j] = '\0';
	ft_strcat(dollar->str, dollar->var);
	if (!dollar->str)
		return ;
	dollar->i += dollar->varname_len + 1;
	dollar->j = ft_strlen(dollar->str);
	while (dollar->line[dollar->i])
		dollar->str[dollar->j++] = dollar->line[dollar->i++];
	dollar->i++;
}

char	*ms_dollar_replacer(t_dollar *dollar)
{
	dollar->var = ft_get_env(dollar->varname);
	if (dollar->var)
	{
		ms_dollar_tailor(dollar);
		free(dollar->line);
		dollar->line = dollar->str;
	}
	ft_strdel(&dollar->varname);
	return (dollar->line);
}

void	ms_dollar_parser(t_token *token, ssize_t *index)
{
	t_dollar	dollar;

	dollar.line = token->str;
	ms_dollar_counter(&dollar, index);
	dollar.i = 0;
	dollar.varname = malloc(sizeof(char) * (dollar.varname_len + 1));
	*index -= dollar.varname_len;
	while (dollar.line[*index] && !ms_dollar_check_charset(dollar.line[*index]))
		dollar.varname[dollar.i++] = dollar.line[(*index)++];
	dollar.varname[dollar.i] = '\0';
	token->str = ms_dollar_replacer(&dollar);
}