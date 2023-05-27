/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:18:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/26 19:40:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	env_util_mode(char **command)
{
	size_t	i;

	i = 1;
	while (command[i])
	{
		if (!is_char_equal(command[i]))
		{
			printf("env: %s: No such file or directory\n", command[i]);
			exit(EXIT_FAILURE);
		}
		printf("%s\n", command[i]);
		i++;
	}
}

void	env_mode(char **command, t_env **env_val)
{
	t_env	*ite;
	size_t	i;

	ite = *env_val;
	while(ite->next != NULL)
	{
		if (ite->value)
			printf("%s=%s\n", ite->name, ite->value);
		ite = ite->next;
	}
	if (arrlen(command) >= 2)
		env_util_mode(command);
}
