/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:40:10 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/08 19:55:58 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static	size_t	count_str(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	cnt;
// 	int		c_flag;

// 	i = 0;
// 	cnt = 0;
// 	c_flag = 0;
// 	while (s[i] != '\0')
// 	{
// 		if ((i == 0 && s[i] != c) || (c_flag == 1 && s[i] != c))
// 		{
// 			cnt++;
// 			c_flag = 0;
// 		}
// 		else if (s[i] == c)
// 			c_flag = 1;
// 		i++;
// 	}
// 	return (cnt);
// }

static	char	*m_str(char const *s, size_t start, size_t end)
{
	char	*ptr;
	size_t	j;

	j = 0;
	ptr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ptr)
		ptr = 0;
	else
	{
		while (start < end)
			ptr[j++] = s[start++];
		ptr[j] = '\0';
	}
	return (ptr);
}

// static	char	**freeall(char **ptr, size_t len, size_t j)
// {
// 	size_t	i;

// 	i = 0;
// 	ptr[j] = 0;
// 	while (j--)
// 	{
// 		if (!ptr[j])
// 		{
// 			while (i <= len)
// 				free(ptr[i++]);
// 			free(ptr);
// 			return (0);
// 		}
// 	}
// 	return (ptr);
// }

char	**split_env(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	ptr = (char **)malloc(sizeof(char *) * 3);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != c)
		i++;
	if (i == 0)
		ptr[0] = NULL;
	else
		ptr[0] = m_str(s, 0, i);
	j = i + 1;
	while (s[++i] != '\0')
	{
	}
	ptr[1] = m_str(s, j, i);
	ptr[2] = NULL;
	return (ptr);
}
