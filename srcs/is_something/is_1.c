/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:45:36 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:45:37 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

bool	is_quotation_mark(char c)
{
	return (c == '\'' || c == '\"');
}

bool	is_endof_env_var(char c)
{
	return (c == ' ' || c == '\"' || c == '\''
		|| c == ';' || c == ':' || c == ',' || c == '.'
		|| c == '/' || c == '\\' || c == '$' || c == '+'
		|| c == '-' || c == '=' || c == '!' || c == '@'
		|| c == '#' || c == '%' || c == '?' || c == '\0');
}

bool	is_endof_str(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '\0');
}
