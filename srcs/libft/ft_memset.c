/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:39:25 by tterao            #+#    #+#             */
/*   Updated: 2023/01/10 16:39:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *buf, int ch, size_t len)
{
	unsigned char	c;
	unsigned char	*strs;

	c = ch;
	strs = (unsigned char *)buf;
	while (len)
	{
		*strs = c;
		strs++;
		len--;
	}
	return (buf);
}
