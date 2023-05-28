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

char	*expand_env_var_helper(char *str, char *expanded_str, size_t *index)
{
	size_t	i;
	size_t	start;

	i = *index;
	while (str[i])
	{
		if (str[i] == '$')
			expanded_str = env_var(str, expanded_str, &i);
		else
		{
			start = i;
			while (str[i] != '\"' && str[i] != '$' && str[i] != '\0')
				i++;
			expanded_str = env_var_helper2(str, expanded_str, start, i);
			if (str[i] == '\"')
			{
				i++;
				break ;
			}
			if (str[i] != '\0')
				i++;
		}
	}

	*index = i;
	return (expanded_str);
}

char	*handle_exp_str(char *str, char *expanded_str,
						size_t *index, bool *d_quotation)
{
	size_t	i;
	size_t	start;

	i = *index;
	start = i;
	if (*d_quotation)
	{
		*d_quotation = !*d_quotation;
		return (expand_env_var_helper(str, expanded_str, index));
	}
	while (!is_endof_str(str[i]))
		i++;
	expanded_str = env_var_helper2(str, expanded_str, start, i);
	*index = i;
	return (expanded_str);
}

char	*handle_single_quotation(char *str, char *expanded_str, size_t *index)
{
	size_t	i;
	size_t	start;
	char	*adding_str;
	char	*tmp;

	i = *index + 1;
	start = i;
	while (str[i] != '\'')
		i++;
	adding_str = ft_substr(str, start, i - start);
	if (!adding_str)
		malloc_failed("malloc");
	if (!expanded_str)
		expanded_str = adding_str;
	else
	{
		tmp = expanded_str;
		expanded_str = ft_strjoin(expanded_str, adding_str);
		free(tmp);
		if (!expanded_str)
			malloc_failed("malloc");
	}
	*index = i + 1;
	return (expanded_str);
}

char	*make_expanded_str(char *str)
{
	size_t	i;
	char	*expanded_str;
	bool	d_quotation;

	i = 0;
	d_quotation = false;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			expanded_str = env_var(str, expanded_str, &i);
		else if (str[i] == '\'')
			expanded_str = handle_single_quotation(str, expanded_str, &i);
		else
		{
			if (str[i] == '\"')
			{
				d_quotation = !d_quotation;
				i++;
			}
			expanded_str = handle_exp_str(str, expanded_str, &i, &d_quotation);
		}
	}
	return (expanded_str);
}

void	expansion(t_token **head)
{
	t_token	*token;

	token = *head;
	while (token)
	{
		if (have_dollarmark(token->str) || have_quotationmark(token->str))
			token->expanded_str = make_expanded_str(token->str);
		else
			token->expanded_str = ft_strdup(token->str);
		if (!token->expanded_str)
			malloc_failed("malloc");
		token = token->next;
	}
}
