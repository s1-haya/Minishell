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

size_t	count_tokens(t_token **head)
{
	size_t	count;
	t_token	*token;

	count = 0;
	token = get_next_token(head);
	while (token)
	{
		if (token->kind == WORD)
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
	// printf("token:%s\n", token->expanded_str);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		malloc_failed("malloc");
	i = 0;
	while (i < len)
	{
		if (token->kind == WORD)
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
