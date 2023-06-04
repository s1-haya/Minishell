/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:01:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 17:01:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_oldpwd(char *pwd, t_env **envs)
{
	char	*old_pwd;

	while (1)
	{
		if (ft_strcmp("OLDPWD", (*envs)->name) == 0)
		{
			old_pwd = (*envs)->value;
			(*envs)->value = pwd;
			free(old_pwd);
			return ;
		}
		(*envs) = (*envs)->next;
	}
}

void	change_pwd(t_env **envs)
{
	char	*new_pwd;
	char	*pwd;
	t_env	*tmp;

	new_pwd = get_pwd();
	tmp = *envs;
	if (new_pwd != NULL)
	{
		g_vars.exit_status = 0;
		while (1)
		{
			if (ft_strcmp("PWD", (*envs)->name) == 0)
			{
				pwd = (*envs)->value;
				(*envs)->value = new_pwd;
				(*envs) = tmp;
				change_oldpwd(pwd, envs);
				break ;
			}
			(*envs) = (*envs)->next;
		}
	}
}