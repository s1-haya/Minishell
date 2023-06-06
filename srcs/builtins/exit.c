/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/06 16:01:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	exit_mode(char **command, t_env **envs)
{
	size_t	i;

	i = 0;
	if (command[1] == NULL)
	{
		printf("exit\n");
		// envs_free(envs);
		exit(EXIT_SUCCESS);
	}
	if (command[1][i] == '\0')
		exit_not_n_faild(command[1]);
	while (command[1][i])
	{
		if (!(ft_isdigit(command[1][i])))
			exit_not_n_faild(command[1]);
		i++;
	}
	if (arrlen(command) >= 3)
	{
		exit_too_many_arguments_faild(command[i]);
		return ;
	}
	printf("exit\n");
	// envs_free(envs);
	exit(ft_atoi(command[1]));
}
