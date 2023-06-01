/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:22:11 by tterao            #+#    #+#             */
/*   Updated: 2023/05/31 16:22:12 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signo)
{
	g_vars.sig_no = signo;
}

void	ft_signal(void)
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) < 0)
		sigaction_failed("sigaction");
	if (sigaction(SIGQUIT, &act, NULL) < 0)
		sigaction_failed("sigaction");
}

void	handle_eof(char *str)
{
	const char	*exit_message = "exit\n";

	if (!str)
	{
		if (write(STDIN_FILENO, exit_message, ft_strlen(exit_message)) < 0)
			write_failed("write");
		exit(g_vars.exit_status);
	}
}
