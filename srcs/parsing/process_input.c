/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:20:12 by albaur            #+#    #+#             */
/*   Updated: 2022/07/26 11:48:40 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isascii(str[i]) == 1 && ft_isspace(str[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

void	process_input(t_data *data)
{
	char	**arr;

	if (check_input(data->input) == 1)
		add_history(data->input);
	if (ft_check_quotes(data->input) > 0)
	{
		ft_printf("\033[31mSyntax error : invalid quote sequence\033[0m\n");
		return ;
	}
	if (check_input(data->input) == 1)
	{
		arr = ms_split(data->input);
		if (arr)
			ft_tokenizer(arr);
	}
	free(data->input);
	builtin_cd_chdir();
	unlink(TMP_FILE);
}
