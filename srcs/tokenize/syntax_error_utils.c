/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:09:57 by tterao            #+#    #+#             */
/*   Updated: 2023/05/24 18:09:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	find_quotation(char *str, char target, size_t *index)
{
	size_t	i;

	i = *index + 1;
	while (str[i])
	{
		if (str[i] == target)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	syntax_error_c(target);
	return (false);
}

bool	is_quotation_closed(t_token **head)
{
	t_token	*token;
	size_t	i;

	token = *head;
	while (token)
	{
		i = 0;
		while (token->str[i])
		{
			if (is_quotation_mark(token->str[i]))
			{
				if (!find_quotation(token->str, token->str[i], &i))
					return (false);
			}
			i++;
		}
		token = token->next;
	}
	return (true);
}

bool	is_invalid_in_value(t_token *token)
{
	const char	*operators[] = {"|", ">", "<", "&", NULL};
	size_t		i;

	if (token->kind != INFILE && token->kind != DELIMITER
		&& token->kind != INSTRING && token->kind != OUTFILE)
		return (false);
	i = 0;
	while (operators[i])
	{
		if (start_with(token->str, operators[i]))
		{
			syntax_error_str(token->str);
			return (true);
		}
		i++;
	}
	return (false);
}
