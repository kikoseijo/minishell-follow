/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:39:48 by albaur            #+#    #+#             */
/*   Updated: 2022/07/25 14:29:45 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_input(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		++i;
	env_set_arg("_", args[i - 1]);
}