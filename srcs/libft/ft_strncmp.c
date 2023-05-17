/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:33:01 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 14:33:03 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				diff;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	diff = 0;
	while (n--)
	{
		diff = *str1 - *str2;
		if (!*str1 || !*str2)
			break ;
		if (diff != 0)
			return (diff);
		str1++;
		str2++;
	}
	return (diff);
}
