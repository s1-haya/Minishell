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

bool	start_with(const char *str, const char *keyword)
{
	return (!ft_memcmp(str, keyword, ft_strlen(keyword))
		&& ft_strlen(str) > ft_strlen(keyword));
}

void	unexpected_token(const char *str, const char *keyword)
{
	size_t	len;

	len = ft_strlen(keyword);
	syntax_error_c(str[len]);
}

bool	is_syntax_error(t_token **head, t_token *token)
{
	const char	*operators[] = {"|", ">>", "<<<", NULL};
	size_t		i;

	i = 0;
	while (operators[i])
	{
		if (start_with(token->str, operators[i]))
		{
			unexpected_token(token->str, operators[i]);
			return (true);
		}
		i++;
	}
	return (false);
}
