/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_output_direction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:37:56 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 14:37:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_output	*malloc_output(void)
{
	t_output	*out;

	out = malloc(sizeof(t_output));
	if (!out)
		malloc_failed("malloc");
	out->outfile = NULL;
	out->have_pipe = false;
	return (out);
}

void	check_pipe(t_token *token, t_output *out)
{
	while (token)
	{
		if (token->kind == PIPE)
		{
			out->have_pipe = true;
			break ;
		}
		token = token->next;
	}
}

t_output	*parse_out_redirection(t_token **head)
{
	t_token		*token;
	t_output	*out;
	bool		out_redirection;

	out_redirection = false;
	token = get_next_token(head);
	out = malloc_output();
	check_pipe(token, out);
	token = parse_out_helper(head, token, out, &out_redirection);
	if (!token && !out_redirection)
		out->kind = STDOUT;
	return (out);
}
