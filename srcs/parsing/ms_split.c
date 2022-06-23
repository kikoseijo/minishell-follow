/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:51 by faventur          #+#    #+#             */
/*   Updated: 2022/06/23 10:49:36 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_oper_writer_index(char *quote, char *str, int *index, int *j)
{
	char	oper;

	oper = str[*index];
	while (str[*index] && str[*index] == oper)
	{
		quote[*j] = str[*index];
		(*j)++;
		(*index)++;
	}
	quote[*j] = '\0';
	printf("oper: %s\n", quote);
	return (quote);
}

int	oper_len_index(char *str, char oper, int *index)
{
	int	counter;

	counter = 0;
	while (str[*index] && str[*index] == oper)
	{
		counter++;
		(*index)++;
	}
	return (counter);
}

int	ft_isoper(char c)
{
	if (c == '<')
		return (1);
	if (c == '|')
		return (2);
	if (c == '>')
		return (3);
	return (0);
}

int	ms_check_charset(char c)
{
	if (ft_isspace(c) || c == '\0')
		return (1);
	return (0);
}

static int	wordgroup_counter(char *s)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			counter += between_squotes(s, &i);
		else if (s[i] == '\"')
			counter += between_dquotes(s, &i);
		else if (ft_isoper(s[i]) && !ft_isoper(s[i + 1]))
		{
			counter++;
			printf("count: %c %d\n", s[i], counter);
		}
		else if (!ms_check_charset(s[i]) && (ms_check_charset(s[i + 1])
				|| ft_isoper(s[i + 1])))
		{
			counter++;
			printf("je rentre ici");
		}
		i++;
	}
	printf("wgcounter: %d\n", counter);
	return (counter);
}

static int	ms_let_count(char *str, int *index)
{
	int		counter;
	char	oper;

	counter = 0;
	while (ms_check_charset(str[*index]))
		(*index)++;
	while (str[*index] && !ms_check_charset(str[*index]))
	{
		if (str[*index] == '\'')
			counter += squote_len_index(str, index);
		else if (str[*index] == '\"')
			counter += dquote_len_index(str, index);
		else if (ft_isoper(str[*index]))
		{
			oper = str[*index];
			counter += oper_len_index(str, oper, index);
		}
		else
		{
			(*index)++;
			counter++;
		}
	}
	return (counter);
}

static char	*wordgroup_split(char *newstr, char *str, int *index)
{
	int	j;

	j = 0;
	while (ms_check_charset(str[*index]))
		(*index)++;
	while (str[*index] && !ms_check_charset(str[*index]))
	{
		if (str[*index] == '\'')
			ft_squote_pruner_index(newstr, str, index, &j);
		else if (str[*index] == '\"')
			ft_dquote_pruner_index(newstr, str, index, &j);
		else if (str[*index] == '\"')
			ft_oper_writer_index(newstr, str, index, &j);
		else
			newstr[j++] = str[(*index)++];
	}
	newstr[j] = '\0';
	return (newstr);
}

char	**ms_split(char *s)
{
	char	**strtab;
	int		size;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	size = wordgroup_counter(s);
	strtab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!strtab)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (k < size)
	{
		strtab[k] = malloc(sizeof(char) * (ms_let_count((char *)s, &i) + 1));
		if (!strtab[k])
			return (NULL);
		wordgroup_split(strtab[k++], (char *)s, &j);
	}
	strtab[k] = NULL;
	return (strtab);
}
