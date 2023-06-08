/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/08 16:21:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_unset(char **command)
{
	size_t	i;

	i = 0;
	if (command[1][0] == '\0')
	{
		printf("unset: `%c': not a valid identifier\n", command[1][0]);
		g_vars.exit_status = 1;
		return (false);
	}
	while (command[++i])
	{
		if (!ft_isalpha(command[i][0]))
		{
			printf("unset: `%s': not a valid identifier\n", command[i]);
			g_vars.exit_status = 1;
			return (false);
		}
	}
	return (true);
}

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
