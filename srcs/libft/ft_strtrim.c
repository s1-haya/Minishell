/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:31:10 by tterao            #+#    #+#             */
/*   Updated: 2023/01/13 14:31:12 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!*set)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] != set[j] && j == ft_strlen(set) - 1)
				return (i);
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
				continue ;
			}
			j++;
		}
		i++;
	}
	return (i);
}

static	size_t	get_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	if (!*set)
		return (i);
	while (1)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] != set[j] && j == ft_strlen(set) - 1)
				return (i);
			if (s1[i] == set[j++])
			{
				i--;
				j = 0;
				continue ;
			}
		}
		if (i == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ptr;
	size_t		start;
	size_t		end;
	size_t		i;

	if (!s1 || !set)
		return (0);
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start < ft_strlen(s1) && start <= end)
		ptr = (char *)malloc(sizeof(char) * (end - start) + 2);
	else
		return (ft_strdup(""));
	if (!ptr)
		return (0);
	i = 0;
	while (start <= end)
		ptr[i++] = s1[start++];
	ptr[i] = 0;
	return (ptr);
}
