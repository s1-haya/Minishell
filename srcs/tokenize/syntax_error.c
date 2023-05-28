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
	return (is_invalid_in_value(token));
}

bool	is_valid_pipe_redirection(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if ((token->kind == PIPE || token->kind == STDIN
				|| token->kind == HEREDOC || token->kind == HERESTRING
				|| token->kind == REDIRECT_OUTPUT || token->kind == APPEND)
			&& !token->next)
		{
			syntax_error_str("newline");
			return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	is_syntax_error(t_token **head)
{
	t_token	*token;

	token = *head;
	if (token && !is_first_token_valid(token))
		return (true);
	while (token)
	{
		if (is_invalid_token(token))
			return (true);
		token = token->next;
	}
	if (!is_valid_pipe_redirection(head))
		return (true);
	if (!is_quotation_closed(head))
		return (true);
	return (false);
}
