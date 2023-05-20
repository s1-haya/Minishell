/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:25:31 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 17:25:33 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lasttoken(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (!token->next)
			break ;
		token = token->next;
	}
	return (token);
}

void	addback(t_token **head, t_token *newtoken)
{
	t_token	*last_token;

	last_token = lasttoken(head);
	if (last_token)
		last_token->next = newtoken;
	else
		*head = newtoken;
}

int	newtoken(t_token **head, char *line, size_t start, size_t end)
{
	t_token	*token;

	if (start == end && line[end] == '\0')
		return (1);
	token = malloc(sizeof(t_token));
	if (!token)
		malloc_failed("malloc");
	token->next = NULL;
	token->is_read = false;
	token->expanded_str = NULL;
	token->str = ft_substr(line, start, (end - start));
	if (!token->str)
		malloc_failed("malloc");
	if ((!ft_strncmp(token->str, "\'\'", 2) || !ft_strncmp(token->str, "\"\"", 2))
		&& ft_strlen(token->str) == 2)
		return (free_token(token));
	if (is_syntax_error(head, token))
		return (2);
	set_token_kind(head, token);
	addback(head, token);
	return (0);
}
