/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:05:06 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 16:05:08 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand(char *str, t_env *envs)
{
	char	*expanded_str;

	expanded_str = expand_env_var(str, envs);
	if (!expanded_str)
		expanded_str = ft_strdup("");
	if (!expanded_str)
		malloc_failed("malloc");
	if (have_quotationmark(expanded_str))
		expanded_str = delete_quotation(expanded_str);
	return (expanded_str);
}

void	expansion(t_token **head, t_env *envs)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (have_dollarmark(token->str) || have_quotationmark(token->str))
			token->expanded_str = expand(token->str, envs);
		else
			token->expanded_str = ft_strdup(token->str);
		if (!token->expanded_str)
			malloc_failed("malloc");
		token = token->next;
	}
}
