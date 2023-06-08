/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:56 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/08 13:43:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins(char **command, t_env **envs)
{
	if (!(ft_strcmp(command[0], "echo")))
		echo_mode(command);
	else if (!(ft_strcmp(command[0], "pwd")))
		pwd_mode();
	else if (!(ft_strcmp(command[0], "cd")))
		cd_mode(command, envs);
	else if (!(ft_strcmp(command[0], "export")))
		export_mode(command, envs);
	else if (!(ft_strcmp(command[0], "env")))
		env_mode(command, envs);
	else if (!(ft_strcmp(command[0], "unset")))
	{
		if (check_unset(command))
			unset_mode(command, envs);
	}
	else if (!(ft_strcmp(command[0], "exit")))
		exit_mode(command);
}

pid_t	output_process(char **command, t_env **envs, t_output *out)
{
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd < 0)
		dup_failed("dup");
	if (!redirect_process(out))
		return (-1);
	builtins(command, envs);
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	return (-1);
}

void	child_builtins(char **command, t_env **envs)
{
	builtins(command, envs);
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
