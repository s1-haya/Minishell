/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:42:04 by tterao            #+#    #+#             */
/*   Updated: 2023/01/19 16:42:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p;

	if (!lst)
		return (0);
	p = lst;
	while (p)
	{
		if (!p->next)
			break ;
		p = p->next;
	}
	return (p);
}
