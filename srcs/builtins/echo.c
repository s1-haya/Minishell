/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:12:40 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/24 14:12:54 by hsawamur         ###   ########.fr       */
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
	exit(EXIT_SUCCESS);
}
