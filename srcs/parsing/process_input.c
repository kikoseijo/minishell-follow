/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:20:12 by albaur            #+#    #+#             */
/*   Updated: 2022/06/25 17:31:54 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(t_data *data)
{
	int		i;
	char	**arr;

	i = 0;
	if (data->input && data->input[0] != '\0' && data->mode)
		add_history(data->input);
	if (check_quotes(data) > 0)
	{
		ft_printf("\033[31mSyntax error : invalid quote sequence\033[0m\n");
		return ;
	}
	//ft_tokenizer(data->input);
	arr = ms_split(data->input);
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
