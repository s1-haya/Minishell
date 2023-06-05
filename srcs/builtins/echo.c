/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:12:40 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/05 12:57:14 by hsawamur         ###   ########.fr       */
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

static void	echo_util_mode(char **command, int space_flag, int output_flag)
{
	size_t	i;

	i = 0;
	while (command[++i])
	{
		if (space_flag)
			printf(" ");
		space_flag = 1;
		if (output_flag)
			printf("%s", command[i]);
		else if (check_option(command[i]))
		{
			printf("%s", command[i]);
			output_flag = 1;
		}
		else
			space_flag = 0;
	}
}

void	echo_mode(char **command)
{
	int		flag;
	int		space_flag;
	int		output_flag;

	space_flag = 0;
	output_flag = 0;
	if (echo_null_check(command[1]))
		return ;
	flag = check_option(command[1]);
	echo_util_mode(command, space_flag, output_flag);
	if (flag)
		printf("\n");
	g_vars.exit_status = 0;
}
