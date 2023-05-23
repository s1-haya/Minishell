/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:24:56 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/23 16:02:58 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_mode(char **command)
{
	size_t	i;
	int		flag;

	printf("echo");
	flag = 1;
	i = 1;
	if (ft_strcmp(command[i], "-n"))
		flag = 0;
	while (command[i])
	{
		printf(" %s", command[i]);
		i++;
	}
	if (flag)
		printf("\n");
	exit(0);
}

void	builtins(char *command)
{
	if (ft_strcmp(command, "echo"))
		echo_mode(command);
}