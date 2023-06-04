/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:14:22 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 17:07:34 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

void	cd_home(t_env **envs)
{
	char	*env;

	env = ft_getenv("HOME", *envs);
	if (env == NULL)
		printf("cd: HOME not set\n");
	else
		chdir(env);
	g_vars.cd_sign = 0;
	change_pwd(envs);
	free(env);
}

void	cd_pwd(t_env **envs)
{
	char	*pwd;

	pwd = ft_getenv("PWD", *envs);
	if (pwd == NULL)
		printf("cd: PWD not set\n");
	else
	{
		printf("%s\n", pwd);
		chdir(pwd);
	}
	g_vars.cd_sign = 0;
	free(pwd);
}

void	cd_oldpwd(t_env **envs)
{
	char	*env;

	env = ft_getenv("OLDPWD", *envs);
	if (env == NULL)
		printf("cd: OLDPWD not set\n");
	else
	{
		printf("%s\n", env);
		chdir(env);
	}
	g_vars.cd_sign = 1;
	free(env);
}

void	cd_mode(char **command, t_env **envs)
{
	t_env		*ite;

	ite = *envs;
	if (command[1] == NULL)
		cd_home(envs);
	else if (ft_strcmp("-", command[1]) == 0)
	{
		g_vars.exit_status = 0;
		if (g_vars.cd_sign)
			cd_pwd(envs);
		else
			cd_oldpwd(envs);
	}
	else
	{
		g_vars.cd_sign = 0;
		if (chdir(command[1]) == -1)
			cd_faild(command[1]);
		else
			change_pwd(envs);
	}
	*envs = ite;
}
