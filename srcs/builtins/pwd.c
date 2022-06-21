/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:52:22 by albaur            #+#    #+#             */
/*   Updated: 2022/06/21 16:26:08 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void pwd(void)
{
	char **env;

	env = env_read(ENV_FILE);
	ft_putendl(env_get("PWD", env));
	free(env);
}
