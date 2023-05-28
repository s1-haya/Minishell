/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:23:26 by tterao            #+#    #+#             */
/*   Updated: 2023/05/26 18:35:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	start_with(const char *str, const char *keyword)
{
	return (!ft_memcmp(str, keyword, ft_strlen(keyword)));
}

bool	is_meta_character(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '>' || c == '<');
}

bool	have_dollarmark(char *str)
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
