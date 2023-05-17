/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:42 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:37:44 by tterao           ###   ########.fr       */
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
	set_token_kind(head, token);
	addback(head, token);
	return (0);
}

size_t	get_end_index(char *line, size_t i)
{
	char	c;

	if (is_quotation_mark(line[i]))
	{
		c = line[i++];
		while (line[i] != c && line[i] != '\0')
			i++;
		if (line[i] != '\0')
			i++;
	}
	else if (is_redirection(line[i]))
	{
		c = line[i];
		while (line[i] == c && line[i] != '\0')
			i++;
	}
	else
	{
		while (!is_space(line[i]) && !is_quotation_mark(line[i])
			&& line[i] != '\0')
			i++;
	}
	return (i);
}

void	tokenize(t_token **head, char *line)
{
	t_token	*token;
	size_t	i;
	size_t	start;

	i = 0;
	while (line[i])
	{
		while (is_space(line[i]) && line[i] != '\0')
			i++;
		start = i;
		i = get_end_index(line, i);
		if (newtoken(head, line, start, i))
			break ;
	}
}
