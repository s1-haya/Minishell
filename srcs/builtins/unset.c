/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:25 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/09 13:21:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_unset(char **command)
{
	size_t	i;
	bool	flag;

	i = 0;
	flag = true;
	if (command[1][0] == '\0')
	{
		printf("unset: `%c': not a valid identifier\n", command[1][0]);
		g_vars.exit_status = 1;
		flag = false;
	}
	while (command[++i])
	{
		if (!ft_isalpha(command[i][0]))
		{
			printf("unset: `%s': not a valid identifier\n", command[i]);
			g_vars.exit_status = 1;
			flag = false;
		}
	}
	return (flag);
}

void	unset_mode(char **command, t_env **envs)
{
	t_env	*curr_env;
	t_env	*pre_env;
	size_t	i;

	i = 0;
	pre_env = NULL;
	while (command[++i])
	{
		curr_env = *envs;
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
