/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:43:24 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 14:43:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*strs;
	unsigned char	target;
	int				diff;

	strs = (unsigned char *)s;
	target = c;
	while (n--)
	{
		diff = *strs - target;
		if (diff == 0)
			return ((void *)strs);
		strs++;
	}
	return (0);
}
