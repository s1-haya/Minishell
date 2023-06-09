/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:18:37 by tterao            #+#    #+#             */
/*   Updated: 2023/06/05 13:18:38 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_heredoc(int signo)
{
	g_vars.sig_no = signo;
	g_vars.exit_status = 1;
	if (close(STDIN_FILENO) < 0)
		close_failed("close");
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		write_failed("write");
}

void	signal_heredoc(int dupped_stdin)
{
	struct sigaction	act;

	if (dup2(dupped_stdin, STDIN_FILENO) < 0)
		dup2_failed("dup2");
	act.sa_handler = signal_handler_heredoc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		sigaction_failed("signal");
	if (sigaction(SIGINT, &act, NULL) < 0)
		sigaction_failed("sigaction");
}

void	put_siginal_msg(int no)
{
	const char	*quit_message = "Quit: 3\n";

	if (no == SIGQUIT)
	{
		if (write(STDOUT_FILENO, quit_message, ft_strlen(quit_message)) < 0)
			write_failed("write");
	}
	else if (no == SIGINT)
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			write_failed("write");
	}
}

void	child_handler(int no)
{
	g_vars.sig_no = no;
	g_vars.sig_no = 0;
}
