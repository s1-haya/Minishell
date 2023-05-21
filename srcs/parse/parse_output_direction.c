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
	return (out);
}

t_output	*parse_out_redirection(t_token **head)
{
	t_token		*token;
	t_output	*out;
	bool		out_redirection;

	out_redirection = false;
	token = get_next_token(head);
	out = malloc_output();
	// printf("parseout token:%s\n", token->expanded_str);
	token = parse_out_helper(head, token, out, &out_redirection);
	// while (token)
	// {
	// 	if (token->is_read)
	// 	{
	// 		token = token->next;
	// 		continue ;
	// 	}
	// 	token->is_read = true;
	// 	if (token->kind == PIPE)
	// 	{
	// 		if (!out_redirection)
	// 			out->kind = PIPE;
	// 		break ;
	// 	}
	// 	if (token->kind == REDIRECT_OUTPUT || token->kind == APPEND)
	// 	{
	// 		out_redirection = true;
	// 		token = create_outfile(token, out);
	// 	}
	// 	if (!token)
	// 	{
	// 		read_till_pipe(head);
	// 		break ;
	// 	}
	// 	token = token->next;
	// }
	// printf("after token:%s\n", token->expanded_str);
	if (!token && !out_redirection)
		out->kind = STDOUT;
	return (out);
}
