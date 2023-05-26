/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:15:25 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 15:15:26 by tterao           ###   ########.fr       */
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

void	execute_fork(t_command_data *d, t_output *out)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		pipe_failed("pipe");
	pid = fork();
	if (pid < 0)
		fork_failed("fork");
	else if (pid == 0)
		child_process(d, out->kind, out->outfile, pipefd);
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
}

void	execute_command(t_token **head, t_command_data *d, t_output *out)
{
	if (out->kind == PIPE)
		execute_fork(d, out);
	else if (out->kind == REDIRECT_OUTPUT)
		execute_fork(d, out);
	else if (out->kind == APPEND)
		execute_fork(d, out);
	else if (out->kind == STDOUT)
		execute_fork(d, out);
	free(out);
}