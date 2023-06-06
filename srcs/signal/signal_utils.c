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
	// if (write(STDIN_FILENO, "\n", 1) < 0)
	// 	write_failed("write");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	signal_heredoc(void)
{
	struct sigaction	act;

	act.sa_handler = signal_handler_heredoc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		sigaction_failed("signal");
	if (sigaction(SIGINT, &act, NULL) < 0)
		sigaction_failed("sigaction");
}

void	parent_signal_handler(int signo)
{
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		write_failed("write");
	g_vars.sig_no = signo;
}

void	child_quit_signal_handler(int signo)
{
	const char	*quit_message = "Quit: 3\n";

	g_vars.sig_no = signo;
	g_vars.exit_status = CHILD_CTRL_Q;
	if (write(STDOUT_FILENO, quit_message, ft_strlen(quit_message)) < 0)
		write_failed("write");
}
