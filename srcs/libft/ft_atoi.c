/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:50:51 by tterao            #+#    #+#             */
/*   Updated: 2023/01/12 19:50:53 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check(char	*str)
{
	if (*str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\v' || *str == ' ')
		return (1);
	return (0);
}

static	long	get_pnum(char *str, long num)
{
	while (*str != '\0')
	{
		if (check(str) == 1)
			break ;
		if (*str < '0' || *str > '9')
			break ;
		if ((LONG_MAX / 10) < (num) || ((LONG_MAX / 10) == (num)
				&& (LONG_MAX % 10) < (*str - '0')))
		{
			num = LONG_MAX;
			break ;
		}
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

static	long	get_mnum(char *str, long num)
{
	while (*str != '\0')
	{
		if (check(str) == 1)
			break ;
		if (*str < '0' || *str > '9')
			break ;
		if ((LONG_MIN / 10) > (num) || ((LONG_MIN / 10) == (num)
				&& (LONG_MIN % 10) > -1 * (*str - '0')))
		{
			num = LONG_MIN;
			break ;
		}
		num = num * 10 + -1 * (*str - '0');
		str++;
	}
	return (num);
}

int	ft_atoi(const char *s)
{
	long	num;
	int		ret;
	int		m_flag;
	char	*str;

	str = (char *)s;
	m_flag = 0;
	while (check(str))
		str++;
	if (*str == '-' && (*(str + 1) >= '0' && *(str + 1) <= '9'))
	{
		m_flag = 1;
		str++;
	}
	else if (*str == '+' && (*(str + 1) >= '0' && *(str + 1) <= '9'))
		str++;
	if (*str < '0' || *str > '9')
		return (0);
	if (m_flag == 0)
		num = get_pnum(str, 0);
	if (m_flag == 1)
		num = get_mnum(str, 0);
	ret = num;
	return (ret);
}
