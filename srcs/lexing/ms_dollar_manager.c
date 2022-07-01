/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:40:42 by faventur          #+#    #+#             */
/*   Updated: 2022/07/01 22:12:01 by faventur         ###   ########.fr       */
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
 * The ft_get_env() function takes an environment variable name as a
 * parameter and returns its content.
 * 
 * The dquote_dollar_replacer() function checks if the environment
 * variable name passed as a parameter corresponds to an existant
 * variable and, if it's the case, replaces it with its content
 * in the new string.
*/

#include "minishell.h"

char	*ft_get_env(char *varname)
{
	char	**arr;
	char	*str;

	arr = env_read(ENV_FILE);
	str = env_get(varname, arr);
	ft_arr_freer(arr);
	return (str);
}

int	dquote_dollar_checker(char *line, size_t *index)
{
	while (line[*index])
	{
		if (line[*index] == '$')
			return (1);
		(*index)++;
	}
	return (0);
}

void	dquote_dollar_counter(t_dollar *dollar, size_t *index)
{
	dollar->varname_len = 0;
	if (dollar->line[*index] == '$')
		(*index)++;
	ft_printf("%d %d\n", *index, dollar->varname_len);
	while (dollar->line[*index] && (!ms_check_charset(dollar->line[*index])
			&& dollar->line[*index] != '\"'))
	{
		ft_printf("boucle %d %d\n", *index, dollar->varname_len);
		dollar->varname_len++;
		(*index)++;
	}
}

char	*dquote_dollar_replacer(t_dollar *dollar)
{
	char	*newstr;
	size_t	i;

	dollar->var = ft_get_env(dollar->varname);
	if (dollar->var)
	{
		i = 0;
		dollar->var_len = ft_strlen(dollar->var);
		dollar->len = ft_strlen(dollar->line) - dollar->varname_len
			+ dollar->var_len;
		ft_printf("count %d\n", dollar->len);
		newstr = malloc(sizeof(char) * (dollar->len + 1));
		if (!newstr)
			return (NULL);
		while (dollar->line[dollar->i] && dollar->line[dollar->i] != '$')
			newstr[i++] = dollar->line[dollar->i++];
		if (dollar->line[dollar->i] == '$')
			newstr[i++] = '\0';
		ft_printf("here we go %s\n", newstr);
		ft_strcat(newstr, dollar->var);
		dollar->i += dollar->varname_len + 1;
		i = ft_strlen(newstr);
		newstr[i++] = dollar->line[dollar->i++];
		dollar->i++;
		ft_printf("here we go %s\n", newstr);
		free(dollar->line);
		ft_printf("here we go %s\n", newstr);
		dollar->line = newstr;
	}
	ft_strdel(&dollar->varname);
	return (dollar->line);
}

void	dquote_dollar_parser(char *line, size_t *index)
{
	t_dollar	dollar;

	if (dquote_dollar_checker(line, index))
	{
		dollar.line = line;
		dquote_dollar_counter(&dollar, index);
		ft_printf("%d\n", dollar.varname_len);
		dollar.i = 0;
		dollar.varname = malloc(sizeof(char) * (dollar.varname_len + 1));
		*index -= dollar.varname_len;
		while (line[*index] && (!ms_check_charset(line[*index])
				&& line[*index] != '\"'))
			dollar.varname[dollar.i++] = line[(*index)++];
		dollar.varname[dollar.i] = '\0';
		dollar.i = 0;
		ft_printf("%d, %s\n", dollar.varname_len, dollar.varname);
		line = dquote_dollar_replacer(&dollar);
		ft_printf("%s\n", dollar.line);
	}
}

void	ms_dollar_manager(char *arr[])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '\"')
				dquote_dollar_parser(arr[i], &j);
			j++;
		}
		i++;
	}
}
