/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:20:12 by albaur            #+#    #+#             */
/*   Updated: 2022/06/21 17:48:40 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_input(t_data *data)
{
	if (data->input && data->input[0] != '\0' && data->mode)
		add_history(data->input);
}
