/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:08:16 by tterao            #+#    #+#             */
/*   Updated: 2023/01/13 19:08:18 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_str(char const *s, char c)
{
	size_t	i;
	size_t	cnt;
	int		c_flag;

	i = 0;
	cnt = 0;
	c_flag = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (c_flag == 1 && s[i] != c))
		{
			cnt++;
			c_flag = 0;
		}
		else if (s[i] == c)
			c_flag = 1;
		i++;
	}
	return (cnt);
}

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

static	char	**freeall(char **ptr, size_t len, size_t j)
{
	size_t	i;

	i = 0;
	ptr[j] = 0;
	while (j--)
	{
		if (!ptr[j])
		{
			while (i <= len)
				free(ptr[i++]);
			free(ptr);
			return (0);
		}
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;
	size_t	start;

	ptr = (char **)malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i == start)
			break ;
		ptr[j++] = m_str(s, start, i);
		if (s[i] != '\0')
			i++;
	}
	ptr = freeall(ptr, count_str(s, c), j);
	return (ptr);
}
