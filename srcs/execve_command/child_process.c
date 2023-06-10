/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:21:41 by tterao            #+#    #+#             */
/*   Updated: 2023/06/07 14:58:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_child_process(t_command_data *d, int *pipefd)
{
	if (close(pipefd[R]) < 0)
		close_failed("close");
	if (have_slash(d->command[0]) && !d->filepath)
	{
		if (close(pipefd[W]) < 0)
			close_failed("close");
		handle_file_dir(d->command[0]);
	}
	if (dup2(pipefd[W], STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(pipefd[W]) < 0)
		close_failed("close");
	if (is_builtin((d->command)[0]))
		child_builtins(d->command, &(d->envs));
	else
		execve(d->filepath, d->command, change_array(d->envs));
	if (d->command[0] && !d->filepath)
		command_not_found(d->command[0]);
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
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (have_slash(d->command[0]) && !d->filepath)
		handle_file_dir(d->command[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
	if (is_builtin((d->command)[0]))
		child_builtins(d->command, &(d->envs));
	else
		execve(d->filepath, d->command, change_array(d->envs));
	if (d->command[0] && !d->filepath)
		command_not_found(d->command[0]);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	append_child_process(t_command_data *d, int *pipefd, char *outfile)
{
	int	fd;

	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (have_slash(d->command[0]) && !d->filepath)
		handle_file_dir(d->command[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
	if (is_builtin((d->command)[0]))
		child_builtins(d->command, &(d->envs));
	else
		execve(d->filepath, d->command, change_array(d->envs));
	if (d->command[0] && !d->filepath)
		command_not_found(d->command[0]);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	stdout_child_process(t_command_data *d, int *pipefd)
{
	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	if (have_slash(d->command[0]) && !d->filepath)
		handle_file_dir(d->command[0]);
	if (is_builtin((d->command)[0]))
		child_builtins(d->command, &(d->envs));
	else
		execve(d->filepath, d->command, change_array(d->envs));
	if (d->command[0] && !d->filepath)
		command_not_found(d->command[0]);
	if (!d->command[0])
		exit(EXIT_SUCCESS);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	child_process(t_command_data *d, t_token_kind output_direction,
						char *outfile, int *pipefd)
{
	if (output_direction == PIPE)
		pipe_child_process(d, pipefd);
	else if (output_direction == REDIRECT_OUTPUT)
		redirect_output_child_process(d, pipefd, outfile);
	else if (output_direction == APPEND)
		append_child_process(d, pipefd, outfile);
	else if (output_direction == STDOUT)
		stdout_child_process(d, pipefd);
}
