/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:37:51 by tterao            #+#    #+#             */
/*   Updated: 2023/06/04 14:34:10 by hsawamur         ###   ########.fr       */
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

bool	have_slash(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (true);
		str++;
	}
	return (false);
}

bool	is_builtin(char *command)
{
	bool	is_builtin;

	is_builtin = false;
	if (command == NULL)
		return (false);
	else if (!(ft_strcmp(command, "echo")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "pwd")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "cd")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "export")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "env")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "unset")))
		is_builtin = true;
	else if (!(ft_strcmp(command, "exit")))
		is_builtin = true;
	return (is_builtin);
}
