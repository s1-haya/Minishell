/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:37:51 by tterao            #+#    #+#             */
/*   Updated: 2023/05/25 15:37:53 by tterao           ###   ########.fr       */
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
