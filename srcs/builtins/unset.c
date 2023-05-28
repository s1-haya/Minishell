/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/28 22:12:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_mode(char **command, t_env **env_val)
{
	t_env	*curr_env;
	t_env	*pre_env;
	size_t	i;

	i = 1;
	curr_env = *env_val;
	pre_env = NULL;
	while (command[i])
	{
		while (curr_env != NULL && ft_strcmp(curr_env->name, command[i]))
		{
			pre_env = curr_env;
			curr_env = curr_env->next;
		}
		if (curr_env != NULL)
		{
			if (pre_env == NULL)
				*env_val = curr_env->next;
			else
				pre_env->next = curr_env->next;
			free(curr_env->name); 
			free(curr_env->value); 
			free(curr_env); 
		}
		i++;
	}
}