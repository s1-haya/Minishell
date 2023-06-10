/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/10 16:40:42 by hsawamur         ###   ########.fr       */
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

void	exit_mode(char **command)
{
	size_t	i;
	int		num;

	i = 0;
	if (command[1] == NULL)
	{
		printf("exit\n");
		exit(g_vars.exit_status);
	}
	if (command[1][i] == '\0')
		exit_n_faild(command[1]);
	if (arrlen(command) >= 3)
	{
		exit_too_many_arguments_faild();
		return ;
	}
	num = ft_atoi(command[1]);
	if (num == 0)
		exit_n_faild(command[1]);
	else
	{
		printf("exit\n");
		exit((unsigned int)num);
	}
}
