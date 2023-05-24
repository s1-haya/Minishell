/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:09:57 by tterao            #+#    #+#             */
/*   Updated: 2023/05/24 18:09:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_invalid_in_value(t_token *token)
{
	const char	*operators[] = {"|", "&", NULL};
	size_t		i;

	if (token->kind != INFILE && token->kind != DELIMITER
		&& token->kind != INSTRING)
		return (false);
	i = 0;
	while (operators[i])
	{
		if (start_with(token->str, operators[i]))
		{
			syntax_error_str(token->str);
			return (true);
		}
		i++;
	}
	return (false);
}
