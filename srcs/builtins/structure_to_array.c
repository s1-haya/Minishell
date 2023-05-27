/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:04:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/27 20:54:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_env(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

static	char	*m_str(char const *s)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	char	**freeall(char **ptr, size_t i)
{
	while (i != -1)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
	return (ptr);
}

static char	*set_env_str(char *name, char *equal, char *value)
{
	char	*env_str;

	env_str = ft_strjoin(name, equal);
	if (!env_str)
		return (NULL);
	env_str = ft_strjoin(env_str, value);
	if (!env_str)
		return (NULL);
	return (env_str);
}

char	**change_array(t_env *env)
{
	char	**env_arr;
	char	*env_str;
	size_t	i;

	env_arr = (char **)malloc(sizeof(char *) * (count_env(env) + 1));
	if (env_arr == NULL)
		return (NULL);
	i = 0;
	while (env)
	{
		env_str = set_env_str(env->name, "=", env->value);
		if (env->value != NULL)
			env_arr[i] = m_str(env_str);
		else
			env_arr[i] = m_str(env->name);
		if (env_arr[i] == NULL)
		{
			freeall(env_arr, i);
			exit(EXIT_FAILURE);
		}
		env = env->next;
		i++;
	}
	return (env_arr);
}