/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:56 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/24 14:07:19 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_mode(char **command)
{
	size_t	i;
	int		flag;
	int		space_flag;

	flag = 1;
	i = 1;
	space_flag = 0;
	if (!ft_strcmp(command[1], "-n"))
	{
		flag = 0;
		i++;
	}
	while (command[i])
	{
		if (space_flag)
			printf(" ");
		space_flag = 1;
		printf("%s", command[i]);
		i++;
	}
	if (flag)
		printf("\n");
	exit(0);
}

void	builtins(char **command)
{
	if (!(ft_strcmp(command[0], "echo")))
	{
		echo_mode(command);
	}
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
//     char *str[] = {"echo", "rizumu", "dddd", "da", NULL};
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