/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:52:29 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 15:52:30 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token **head)
{
	t_token	*token;
	t_token	*tmp;

	token = *head;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp->expanded_str);
		free(tmp);
	}
}
