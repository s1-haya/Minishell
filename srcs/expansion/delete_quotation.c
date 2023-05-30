/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:06:00 by tterao            #+#    #+#             */
/*   Updated: 2023/05/30 15:06:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*substr_exp_dq(char *str, char *expanded_str, size_t start, size_t end)
{
	char	*adding_str;
	char	*new_expanded_str;

	if (end == start)
		adding_str = ft_strdup("");
	else
		adding_str = ft_substr(str, start, end - start);
	if (!adding_str)
		malloc_failed("malloc");
	if (!expanded_str)
		return (adding_str);
	new_expanded_str = ft_strjoin(expanded_str, adding_str);
	free(expanded_str);
	free(adding_str);
	if (!new_expanded_str)
		malloc_failed("malloc");
	return (new_expanded_str);
}

char	*delete_quotation_helper(char *str, char *expanded_str,
									size_t start, size_t end)
{
	expanded_str = substr_exp_dq(str, expanded_str, start, end);
	free(str);
	return (expanded_str);
}

void	reset_ep_q_vars(size_t *start, size_t *i, bool *quotation)
{
	*start = *i;
	*quotation = !*quotation;
}

void	*init_ep_q_vars(size_t *i, size_t *start, bool *quotation)
{
	*i = 0;
	*start = 0;
	*quotation = false;
	return (NULL);
}

char	*delete_quotation(char *str)
{
	char	*expanded_str;
	size_t	i;
	size_t	start;
	char	target;
	bool	quotation;

	expanded_str = init_ep_q_vars(&i, &start, &quotation);
	i = 0;
	while (str[i])
	{
		if (quotation && str[i] == target)
		{
			expanded_str = substr_exp_dq(str, expanded_str, start, i++);
			reset_ep_q_vars(&start, &i, &quotation);
		}
		else if (is_quotation_mark(str[i]) && !quotation)
		{
			expanded_str = substr_exp_dq(str, expanded_str, start, i);
			target = str[i++];
			reset_ep_q_vars(&start, &i, &quotation);
		}
		else
			i++;
	}
	return (delete_quotation_helper(str, expanded_str, start, i));
}
