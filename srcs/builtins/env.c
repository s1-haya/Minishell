/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:18:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/26 16:49:01 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_mode(char **command, t_env **env_val)
{
	extern char **environ;
	char **env;
	const char	*val;

	env = environ;
	while(*env)
	{
		val = *env;
		if (val)
			printf("%s\n", val);
		env++;
	}
	if (arrlen(command) == 2)
	{
		*env = command[1];
		printf("%s\n", *env);
	}
}
