/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:45:37 by albaur            #+#    #+#             */
/*   Updated: 2022/06/21 18:03:59 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	if (argc > 1 && argv)
		throw_error(data, "Error", E2BIG);
	init_shell(data);
	while (!data->exit)
	{
		data->input = readline(ft_strjoin(env_get_pwd(), " $ "));
		if (data->input == NULL)
			break ;
		process_input(data);
		free(data->input);
	}
	unlink(ENV_FILE);
	return (0);
}
