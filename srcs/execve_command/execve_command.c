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
		syntax_error(token->expanded_str);
	token->is_read = true;
	return (token->expanded_str);
}

void	execute_fork(t_command_data *d, int output_direction, char *outfile)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		pipe_failed("pipe");
	pid = fork();
	if (pid < 0)
		fork_failed("fork");
	else if (pid == 0)
		child_process(d, output_direction, outfile, pipefd);
	else
	{
		if (output_direction == PIPE)
		{
			if (dup2(pipefd[R], STDIN_FILENO) < 0)
				dup2_failed("dup2");
		}
		if (close(pipefd[R]) + close(pipefd[W]) < 0)
			close_failed("close");
	}
}

void	execute_command(t_token **head, t_command_data *d,
						t_token_kind output_direction)
{
	if (output_direction == PIPE)
		execute_fork(d, output_direction, NULL);
	else if (output_direction == REDIRECT_OUTPUT)
		execute_fork(d, output_direction, get_output_file(head));
	else if (output_direction == APPEND)
		execute_fork(d, output_direction, get_output_file(head));
	else if (output_direction == STDOUT)
		execute_fork(d, output_direction, NULL);
}
