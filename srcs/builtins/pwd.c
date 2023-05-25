/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/25 14:30:58 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# define PATH_SIZE (512)

static size_t	arrlen(char **command)
{
	size_t	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

void	pwd_mode(char **command)
{
	char	pwd[PATH_SIZE];

	if (arrlen(command) != 1)
	{
		printf("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (getcwd(pwd, PATH_SIZE) == NULL)
		exit(EXIT_FAILURE);
	printf("%s\n", pwd);
	exit(EXIT_SUCCESS);
}
