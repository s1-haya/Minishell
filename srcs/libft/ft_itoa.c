/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:35:47 by tterao            #+#    #+#             */
/*   Updated: 2023/01/14 17:35:48 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_degit(int n)
{
	long	num;
	size_t	cnt;

	cnt = 1;
	num = 0;
	if (n < 0)
	{
		num = n;
		num *= -1;
		cnt++;
	}
	else
		num = n;
	while (num > 9)
	{
		num /= 10;
		cnt++;
	}
	return (cnt++);
}

static	void	allocate_nums(char	*ptr, int n)
{
	size_t	check;
	int		m_flag;
	long	num;

	num = n;
	m_flag = 0;
	check = get_degit(n);
	ptr[check] = 0;
	if (num < 0)
	{
		num *= -1;
		ptr[0] = '-';
		m_flag = 1;
	}
	while (check--)
	{
		if (m_flag == 1 && check == 0)
			break ;
		ptr[check] = num % 10 + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (get_degit(n) + 1));
	if (!ptr)
		return (0);
	allocate_nums(ptr, n);
	return (ptr);
}
