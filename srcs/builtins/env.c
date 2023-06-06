/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:18:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/05 16:02:19 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_mode(char **command, t_env **envs)
{
	t_env	*ite;
	size_t	i;

	if (command[1] == NULL)
	{
		ite = *envs;
		while (ite != NULL)
		{
			if (ite->value != NULL)
			{
				if (ite->value)
					printf("%s=%s\n", ite->name, ite->value);
				else
					printf("%s=\n", ite->name);
			}
			ite = ite->next;
		}
		g_vars.exit_status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n", command[1]);
		g_vars.exit_status = COMMAND_NOT_FOUND;
	}
}
