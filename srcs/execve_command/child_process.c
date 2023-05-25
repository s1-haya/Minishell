/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:21:41 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 15:21:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_child_process(t_command_data *d, int *pipefd)
{
	if (close(pipefd[R]) < 0)
		close_failed("close");
	if ((d->command[0] || d->command[0][0] == '\0') && !d->filepath)
		command_not_found(d->command[0]);
	if (dup2(pipefd[W], STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(pipefd[W]) < 0)
		close_failed("close");
	execve(d->filepath, d->command, d->envp);
	// execve_failed("execve");
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	redirect_output_child_process(t_command_data *d, int *pipefd,
										char *outfile)
{
	int	fd;

	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	if (!outfile)
	{
		syntax_error_str("newline");
		exit(SYNTAX_ERROR);
	}
	if ((d->command[0] || d->command[0][0] == '\0') && !d->filepath)
		command_not_found(d->command[0]);
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
	execve(d->filepath, d->command, d->envp);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
// execve_failed("execve");
	exit(COMMAND_NOT_EXECUTABLE);
}

void	append_child_process(t_command_data *d, int *pipefd, char *outfile)
{
	int	fd;

	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	if (!outfile)
	{
		syntax_error_str("newline");
		exit(SYNTAX_ERROR);
	}
	if ((d->command[0] || d->command[0][0] == '\0') && !d->filepath)
		command_not_found(d->command[0]);
	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
	execve(d->filepath, d->command, d->envp);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	// execve_failed("execve");
	exit(COMMAND_NOT_EXECUTABLE);
}

void	stdout_child_process(t_command_data *d, int *pipefd)
{
	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	// printf("stdout_child_process:%s\n", d->filepath);
	execve(d->filepath, d->command, d->envp);
	// execve_failed("execve");
	if ((d->command[0] || d->command[0][0] == '\0') && !d->filepath)
		command_not_found(d->command[0]);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	child_process(t_command_data *d, t_token_kind output_direction,
						char *outfile, int *pipefd)
{
	// printf("direction:%d\n", output_direction);
	if (output_direction == PIPE)
		pipe_child_process(d, pipefd);
	else if (output_direction == REDIRECT_OUTPUT)
		redirect_output_child_process(d, pipefd, outfile);
	else if (output_direction == APPEND)
		append_child_process(d, pipefd, outfile);
	else if (output_direction == STDOUT)
		stdout_child_process(d, pipefd);
}
