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

char	*malloc_null(char *expanded_str)
{
	if (!expanded_str)
		expanded_str = ft_strdup("\0");
	if (!expanded_str)
		malloc_failed("malloc");
	return (expanded_str);
}

char	*env_var_helper2(char *str, char *expanded_str, size_t start, size_t end)
{
	char	*adding_str;
	char	*tmp;

	if (start == end)
		return (malloc_null(expanded_str));
	if (!expanded_str)
		expanded_str = ft_substr(str, start, (end - start));
	else
	{
		adding_str = ft_substr(str, start, (end - start));
		if (!adding_str)
			malloc_failed("malloc");
		tmp = expanded_str;
		expanded_str = ft_strjoin(expanded_str, adding_str);
		free(adding_str);
		free(tmp);
	}
	if (!expanded_str)
		malloc_failed("malloc");
	return (expanded_str);
}

char	*env_ver_join(char *env, char *expanded_str)
{
	char	*tmp;

	if (!expanded_str)
		expanded_str = ft_strdup(env);
	else
	{
		tmp = expanded_str;
		expanded_str = ft_strjoin(expanded_str, env);
		free(tmp);
	}
	if (!expanded_str)
		malloc_failed("malloc");
	return (expanded_str);
}

char	*env_var_helper1(char *str, char *expanded_str, size_t start, size_t end)
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
			return (expanded_str);
	}
	return (env_ver_join(env, expanded_str));
}

char	*env_var(char *str, char *expanded_str, size_t *index)
{
	size_t	i;
	size_t	start;
	char	*ret;

	i = *index;
	start = i++;
	if (str[i] == '?')
		i++;
	else
	{
		while (!is_endof_env_var(str[i]))
			i++;
	}
	ret = env_var_helper1(str, expanded_str, start, i);
	*index = i;
	return (ret);
}
