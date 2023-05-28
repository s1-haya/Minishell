/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/25 21:37:00 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_mode(char **command)
{
	char	pwd[BUFFERSIZE];

	if (arrlen(command) != 1)
	{
		printf("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (getcwd(pwd, BUFFERSIZE) == NULL)
		exit(EXIT_FAILURE);
	printf("%s\n", pwd);
	exit(EXIT_SUCCESS);
}
