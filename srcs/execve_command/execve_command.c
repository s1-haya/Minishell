/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:15:25 by tterao            #+#    #+#             */
/*   Updated: 2023/06/06 14:37:29 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_output_file(t_token **head)
{
	t_token	*token;

	token = get_next_token(head);
	if (!token)
		return (NULL);
	token->is_read = true;
	return (token->expanded_str);
}

pid_t	execute_fork(t_command_data *d, t_output *out)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		pipe_failed("pipe");
	pid = fork();
	if (pid < 0)
		fork_failed("fork");
	else if (pid == 0)
	{
		ft_signal(CHILD);
		child_process(d, out->kind, out->outfile, pipefd);
	}
	else
	{
		if (out->have_pipe)
		{
			if (dup2(pipefd[R], STDIN_FILENO) < 0)
				dup2_failed("dup2");
		}
		if (close(pipefd[R]) + close(pipefd[W]) < 0)
			close_failed("close");
	}
	return (pid);
}

pid_t	execute_command(t_command_data *d, t_output *out)
{
	pid_t	pid;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		sigaction_failed("signal");
	ft_signal(PARENT);
	pid = execute_fork(d, out);
	free(out);
	return (pid);
}
