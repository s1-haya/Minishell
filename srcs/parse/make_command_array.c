/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:44 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 14:17:45 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_skipping(t_token *token)
{
	if (token->str[0] == '$' && token->expanded_str[0] == '\0')
	{
		token->is_read = true;
		return (true);
	}
	return (false);
}

size_t	count_tokens(t_token **head)
{
	size_t	count;
	t_token	*token;

	count = 0;
	token = get_next_token(head);
	while (token)
	{
		if (token->kind == WORD && !is_skipping(token))
			count++;
		if (token->kind == PIPE)
			break ;
		token = token->next;
	}
	return (count);
}

char	**make_command_array(t_token **head)
{
	char	**array;
	t_token	*token;
	size_t	i;
	size_t	len;

	token = get_next_token(head);
	len = count_tokens(head);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		malloc_failed("malloc");
	i = 0;
	while (i < len)
	{
		if (token->kind == WORD && !token->is_read)
		{
			array[i] = ft_strdup(token->expanded_str);
			if (!array[i++])
				malloc_failed("malloc");
			token->is_read = true;
		}
		token = token->next;
	}
	array[i] = NULL;
	return (array);
}
