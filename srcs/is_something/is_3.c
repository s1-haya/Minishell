/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:37:51 by tterao            #+#    #+#             */
/*   Updated: 2023/05/28 19:06:36 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	have_quotationmark(char *str)
{
	while (*str)
	{
		if (is_quotation_mark(*str))
			return (true);
		str++;
	}
	return (false);
}

bool	is_char_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (true);
		str++;
	}
	return (false);
}
