/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:03:54 by albaur            #+#    #+#             */
/*   Updated: 2022/07/24 11:26:56 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		env_set_arg("?heredoc", "sigint");
		ft_putendl("");
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		ft_putendl("");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		ft_putendl_fd("minishell: quit", 2);
}

void	sig_int_nl(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putendl("");
}
