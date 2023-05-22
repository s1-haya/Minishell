/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:23:26 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 18:23:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_eoc(char c)
{
	return (c == '|' || c == '>');
}

bool	start_with(const char *str, const char *keyword)
{
	return (!ft_memcmp(str, keyword, ft_strlen(keyword)));
}

bool	is_meta_character(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>' || c == '<');
}

bool	have_dollermark(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (true);
		str++;
	}
	return (false);
}

bool	only_space(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (false);
		str++;
	}
	return (true);
}
