/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:39:07 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 16:39:09 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_var_helper2(char *str, char *new_str, size_t start, size_t end)
{
	char	*adding_str;
	char	*tmp;

	if (!new_str)
		new_str = ft_substr(str, start, (end - start));
	else
	{
		adding_str = ft_substr(str, start, (end - start));
		if (!adding_str)
			malloc_failed("malloc");
		tmp = new_str;
		new_str = ft_strjoin(new_str, adding_str);
		free(adding_str);
		free(tmp);
	}
	if (!new_str)
		malloc_failed("malloc");
	return (new_str);
}

char	*env_ver_join(char *env, char *new_str)
{
	char	*tmp;

	if (!new_str)
		new_str = ft_strdup(env);
	else
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, env);
		free(tmp);
	}
	if (!new_str)
		malloc_failed("malloc");
	return (new_str);
}

char	*env_var_helper1(char *str, char *new_str, size_t start, size_t end)
{
	char	*env;
	char	*tmp;

	if (end - start > 1)
		start++;
	tmp = ft_substr(str, start, (end - start));
	if (!tmp)
		malloc_failed("malloc");
	if (ft_strlen(tmp) == 1 && tmp[0] == '?')
	{
		free(tmp);
		env = ft_itoa(g_status);
	}
	else if (tmp[0] == '$')
		env = tmp;
	else
	{
		env = getenv(tmp);
		free(tmp);
		if (!env)
			return (new_str);
	}
	return (env_ver_join(env, new_str));
}
