/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:48:03 by faventur          #+#    #+#             */
/*   Updated: 2022/06/23 14:38:05 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			++i;
		else if (str[i] == '|')
			++counter;
		++i;
	}
	return (counter);
}

int	parg_size(char *str, int i)
{
	int	counter;

	counter = 0;
	while (str[i])
	{
		if (str[i - 1] != '|' && str[i] == '|' && str[i + 1] != '|')
			break ;
		++counter;
		++i;
	}
	++counter;
	return (counter);
}

char	*parg_writer(char *dst, char *src, int *i)
{
	int	j;

	j = 0;
	while (src[*i])
	{
		dst[j] = src[*i];
		if (src[*i - 1] != '|' && src[*i] == '|' && src[*i + 1] != '|')
			break ;
		++(*i);
		++j;
	}
	++(*i);
	dst[j] = '\0';
	return (dst);
}

char	**parg_cut(char *str)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (pipe_counter(str) + 2));
	if (!arr)
		return (NULL);
	while (i < pipe_counter(str) + 1)
	{
		arr[i] = malloc(sizeof(char) * (parg_size(str, j)));
		if (!arr[i])
			return (NULL);
		arr[i] = parg_writer(arr[i], str, &j);
		++i;
	}
	arr[i] = NULL;
	return (arr);
}