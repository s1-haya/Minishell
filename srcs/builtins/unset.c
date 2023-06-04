/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 13:15:21 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_mode(char **command, t_env **envs)
{
	t_env	*curr_env;
	t_env	*pre_env;
	size_t	i;

	i = 0;
	curr_env = *envs;
	pre_env = NULL;
	while (command[++i])
	{
		while (curr_env != NULL && ft_strcmp(curr_env->name, command[i]))
		{
			pre_env = curr_env;
			curr_env = curr_env->next;
		}
		if (curr_env != NULL)
		{
			if (pre_env == NULL)
				*envs = curr_env->next;
			else
				pre_env->next = curr_env->next;
			free(curr_env->name);
			free(curr_env->value);
			free(curr_env);
		}
	}
}
