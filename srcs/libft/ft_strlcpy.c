/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:05:12 by tterao            #+#    #+#             */
/*   Updated: 2023/01/11 19:05:14 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	ret;

	ret = ft_strlen(src);
	if (destsize == 0)
		return (ret);
	i = 0;
	while (i < destsize - 1)
	{
		if (src[i] == '\0')
			break ;
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ret);
}
