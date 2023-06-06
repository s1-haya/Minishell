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

void	ctrl_c(void)
{
	g_vars.sig_no = 0;
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		write_failed("write");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(int signo)
{
	g_vars.sig_no = signo;
	g_vars.exit_status = 1;
	ctrl_c();
}

void	child_sigint_signal_handler(int signo)
{
	g_vars.sig_no = signo;
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		write_failed("write");
	g_vars.sig_no = 0;
}

void	ft_signal(enum e_signal no)
{
	struct sigaction	act;

	if (no == DEFAULT)
		act.sa_handler = signal_handler;
	else
		act.sa_handler = child_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) < 0)
		sigaction_failed("sigaction");
	if (no != CHILD)
	{
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			sigaction_failed("signal");
	}
	else
	{
		act.sa_handler = child_handler;
		if (sigaction(SIGQUIT, &act, NULL) < 0)
			sigaction_failed("sigaction");
	}
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
