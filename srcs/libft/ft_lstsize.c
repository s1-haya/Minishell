/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:06:00 by tterao            #+#    #+#             */
/*   Updated: 2023/01/19 16:06:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*p;

	if (lst == 0)
		return (0);
	p = lst->next;
	len = 1;
	while (p)
	{
		p = p->next;
		len++;
	}
	return (len);
}
