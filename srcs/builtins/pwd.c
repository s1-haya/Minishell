/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 13:13:35 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_vars.exit_status = 1;
		perror("pwd");
	}
	return (pwd);
}

void	pwd_mode(char **command)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd != NULL)
	{
		g_vars.exit_status = 0;
		printf("%s\n", pwd);
	}
	free(pwd);
}
