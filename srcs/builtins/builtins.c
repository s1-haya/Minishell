/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:56 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/06 18:01:28 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_output_process(char *outfile)
{
	int	fd;

	if (!outfile)
	{
		syntax_error_str("newline");
		exit(SYNTAX_ERROR);
	}
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
}

void	append_process(char *outfile)
{
	int	fd;

	if (!outfile)
	{
		syntax_error_str("newline");
		exit(SYNTAX_ERROR);
	}
	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
		open_failed_exit(outfile);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
}

void	output_process(t_output *out)
{
	if (out == NULL)
		return ;
	else if (out->kind == REDIRECT_OUTPUT)
		redirect_output_process(out->outfile);
	else if (out->kind == APPEND)
		append_process(out->outfile);
}

pid_t	builtins(char **command, t_env **envs, t_output *out)
{
	int	fd;
	int	fd2;

	fd = dup(STDOUT_FILENO);
	if (fd < 0)
		dup_failed("dup");
	output_process(out);
	if (!(ft_strcmp(command[0], "echo")))
		echo_mode(command);
	else if (!(ft_strcmp(command[0], "pwd")))
		pwd_mode(command);
	else if (!(ft_strcmp(command[0], "cd")))
		cd_mode(command, envs);
	else if (!(ft_strcmp(command[0], "export")))
		export_mode(command, envs);
	else if (!(ft_strcmp(command[0], "env")))
		env_mode(command, envs);
	else if (!(ft_strcmp(command[0], "unset")))
		unset_mode(command, envs);
	else if (!(ft_strcmp(command[0], "exit")))
		exit_mode(command, envs);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	free(out);
	return (-1);
}

void	child_builtins(char **command, t_env **envs)
{
	builtins(command, envs, NULL);
	exit(g_vars.exit_status);
}

// int main(void)
// {
// 	char	str[][3] = {"echo", "rizumu"};
// 	builtins(str);
// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// size_t	arr_len(char **arr)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arr[i])
// 		i++;
// 	return (i);
// }

// int main(void)
// {
//     char *str[] = {"pwd", "rizumu", "dddd", "da", NULL};
// 	size_t len = arr_len(str);
// 	// printf("size %zu\n", len);
// 	// exit(0);
//     char **commands = malloc(sizeof(char*) * (len + 1));

//     for (int i = 0; i < len; i++) {
//         commands[i] = malloc(strlen(str[i]) + 1);
//         strcpy(commands[i], str[i]);
//     }
// 	commands[len] = NULL;
//     builtins(commands);

//     // Free the allocated memory
//     for (int i = 0; i < len; i++) {
//         free(commands[i]);
//     }
//     free(commands);

//     return 0;
// }
