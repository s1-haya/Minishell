/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:24:36 by tterao            #+#    #+#             */
/*   Updated: 2023/05/20 16:24:38 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unexpected_token(const char *str, const char *keyword)
{
	size_t	len;

	len = ft_strlen(keyword);
	syntax_error_c(str[len]);
}

bool	is_first_token_valid(t_token *token)
{
	const char	*operators[] = {"|", "&", NULL};
	size_t		i;

	i = 0;
	while (operators[i])
	{
		if (start_with(token->str, operators[i]))
		{
			syntax_error_str(token->str);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_invalid_token(t_token *token)
{
	const char	*operators[] = {"|", ">>", "<<<", NULL};
	size_t		i;

	i = 0;
	while (operators[i])
	{
		if (start_with(token->str, operators[i])
			&& ft_strlen(token->str) > ft_strlen(operators[i]))
		{
			unexpected_token(token->str, operators[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_valid_redirection(t_token **head)
{
	t_token	*token;

	token = *head;
	if (token && start_with(token->str, ">") && !token->next)
	{
		syntax_error_str("newline");
		return (false);
	}
	return (true);
}

bool	is_syntax_error(t_token **head)
{
	t_token	*token;

	if (!*head && !is_first_token_valid(token))
		return (true);
	token = *head;
	while (token)
	{
		if (is_invalid_token(token))
			return (true);
		token = token->next;
	}
	if (!is_valid_redirection(head))
		return (true);
	return (false);
}
