/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:25:28 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 20:25:29 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*p;
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
