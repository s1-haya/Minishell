/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:17:51 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 19:17:53 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*h;
	size_t		needle_len;

	h = (char *)haystack;
	if (!*needle)
		return (h);
	needle_len = ft_strlen(needle);
	while (len)
	{
		if (needle_len > len)
			return (0);
		if (ft_strncmp(h, needle, needle_len) == 0)
			return (h);
		if (!*h)
			break ;
		len--;
		h++;
	}
	return (0);
}
