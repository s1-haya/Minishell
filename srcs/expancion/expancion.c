/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:05:06 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 16:05:08 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_env_var_helper(char *str, char *new_str, size_t *index)
{
	size_t	i;
	size_t	start;

	i = *index;
	if (str[i] == '\"')
			i++;
	else if (str[i] == '$')
	{
		start = i++;
		while (!is_endof_env_var(str[i]))
			i++;
		new_str = env_var_helper1(str, new_str, start, i);
	}
	else
	{
		start = i;
		while (!is_endof_str(str[i]))
			i++;
		new_str = env_var_helper2(str, new_str, start, i);
	}
	*index = i;
	return (new_str);
}

char	*expand_env_var(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	start;

	i = 0;
	new_str = NULL;
	while (str[i])
		new_str = expand_env_var_helper(str, new_str, &i);
	return (new_str);
}

bool	have_env_var(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (true);
		str++;
	}
	return (false);
}

void	make_expanded_str(t_token *node)
{
	if (is_quotation_mark(node->str[0]) || node->str[0] == '$')
	{
		if (node->str[0] != '\'' && have_env_var(node->str))
			node->expanded_str = expand_env_var(node->str);
		else
			node->expanded_str = ft_substr
				(node->str, 1, ft_strlen(node->str) - 2);
	}
	else
		node->expanded_str = ft_strdup(node->str);
}

void	expancion(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		make_expanded_str(token);
		token = token->next;
	}
}
