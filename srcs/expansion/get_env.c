/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:46:27 by tterao            #+#    #+#             */
/*   Updated: 2023/05/28 21:46:29 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_exp_ev(char *env, t_env *envs)
{
	char	*tmp;
	bool	free_flag;

	tmp = env;
	free_flag = true;
	if (!ft_strncmp(env, "$?", ft_strlen(env)) && ft_strlen(env) == 2)
	{
		env = ft_itoa(g_status);
		if (!env)
			malloc_failed("malloc");
	}
	else if (!ft_strncmp(env, "$", ft_strlen(env)) && ft_strlen(env) == 1)
		free_flag = false;
	else
		env = ft_getenv(env, envs);
	if (free_flag)
		free(tmp);
	return (env);
}

char	*ft_getenv(char *target, t_env *envs)
{
	t_env	*token;
	char	*env;

	token = envs;
	while (token)
	{
		if (!ft_strncmp(target, token->name, ft_strlen(target))
			&& ft_strlen(target) == ft_strlen(token->name) && token->value)
		{
			env = ft_strdup(token->value);
			if (!env)
				malloc_failed("malloc");
			return (env);
		}
		token = token->next;
	}
	return (NULL);
}
