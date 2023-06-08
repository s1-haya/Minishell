/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/08 14:41:31 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_free(t_env *env)
{
	free(env->name);
	env->name = NULL;
	free(env->value);
	env->value = NULL;
	free(env->next);
	env->next = NULL;
	free(env);
	env = NULL;
}

void	envs_free(t_env **envs)
{
	t_env	*tmp;

	while ((*envs))
	{
		free((*envs)->name);
		(*envs)->name = NULL;
		free((*envs)->value);
		(*envs)->value = NULL;
		tmp = (*envs);
		(*envs) = (*envs)->next;
		free(tmp->next);
		(*envs)->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	exit_mode(char **command)
{
	size_t	i;

	i = 0;
	if (command[1] == NULL)
	{
		printf("exit\n");
		exit(g_vars.exit_status);
	}
	if (command[1][i] == '\0')
		exit_n_faild(command[1]);
	while (command[1][i])
	{
		if (!(ft_isdigit(command[1][i])))
			exit_n_faild(command[1]);
		i++;
	}
	if (arrlen(command) >= 3)
	{
		exit_too_many_arguments_faild();
		return ;
	}
	printf("exit\n");
	exit(ft_atoi(command[1]));
}
