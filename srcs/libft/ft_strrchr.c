/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:11:10 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 14:11:13 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	size_t	len;
	size_t	i;

	s = (char *)str;
	if (c < 0)
	{
		c %= 256;
		c += 256;
	}
	if (c > 255)
		c %= 256;
	len = ft_strlen(s);
	s += len;
	i = 0;
	while (i <= len)
	{
		if (*s == c)
			return (s);
		s--;
		i++;
	}
	return (0);
}
