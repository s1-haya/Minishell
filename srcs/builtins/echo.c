/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:12:40 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 14:26:56 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_option(char *command)
{
	size_t	i;

	if (!ft_strcmp(command, "-n"))
		return (0);
	i = 0;
	if (!(command[i] == '-'))
		return (1);
	while (command[++i])
	{
		if (!(command[i] == 'n'))
			return (1);
	}
	return (0);
}

bool	echo_null_check(char *command)
{
	if (command == NULL)
	{
		printf("\n");
		return (true);
	}
	return (false);
}

void	echo_mode(char **command)
{
	size_t	i;
	int		flag;
	int		space_flag;

	i = 1;
	space_flag = 0;
	if (echo_null_check(command[i]))
		return ;
	flag = check_option(command[i]);
	while (command[i])
	{
		if (space_flag)
			printf(" ");
		space_flag = 1;
		if (check_option(command[i]))
			printf("%s", command[i]);
		else
			space_flag = 0;
		i++;
	}
	if (flag)
		printf("\n");
}
