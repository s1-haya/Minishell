/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:50:43 by tterao            #+#    #+#             */
/*   Updated: 2023/01/11 19:50:45 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!destsize)
		len = ft_strlen(src);
	else if (destsize <= ft_strlen(dest))
		len = ft_strlen(src) + destsize;
	else
	{
		len = ft_strlen(src) + ft_strlen(dest);
		i = 0;
		while (dest[i] != '\0')
			i++;
		j = 0;
		while (i < destsize - 1)
		{
			if (src[j] == '\0')
				break ;
			dest[i++] = src[j++];
		}
		dest[i] = '\0';
	}
	return (len);
}
