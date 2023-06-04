/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:18:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 13:24:11 by hsawamur         ###   ########.fr       */
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
	}
}
