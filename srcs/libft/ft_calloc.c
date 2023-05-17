/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:26:38 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 20:26:40 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	cal;
	size_t	check;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	cal = count * size;
	if (size != 0)
	{
		check = cal / size;
		if (check != count)
			return (0);
	}
	ptr = (void *)malloc(cal);
	if (!ptr)
		return (0);
	ft_bzero(ptr, cal);
	return (ptr);
}
