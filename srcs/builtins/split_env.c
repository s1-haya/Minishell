/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:40:10 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/09 14:53:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*m_str(char const *s, size_t start, size_t end)
{
	char	*ptr;
	size_t	j;

	j = 0;
	if (start >= end)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ptr)
		malloc_failed("malloc");
	else
	{
		while (start < end)
			ptr[j++] = s[start++];
		ptr[j] = '\0';
	}
	return (ptr);
}

size_t	split_c_sign(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*env_name(char *env)
{
	if (env[0] == '=')
		return (NULL);
	return (m_str(env, 0, split_c_sign(env, '=')));
}

char	*env_value(char *env)
{
	if (!(is_char_equal(env)))
		return (NULL);
	return (m_str(env, split_c_sign(env, '=') + 1, ft_strlen(env)));
}
