/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:53:49 by tterao            #+#    #+#             */
/*   Updated: 2023/05/21 19:53:51 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_outfile(t_token *token, t_output *out)
{
	t_token	*outfile;
	int		fd;

	out->kind = token->kind;
	outfile = token->next;
	outfile->is_read = true;
	out->outfile = outfile->expanded_str;
	fd = open(outfile->expanded_str, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		return (NULL);
	if (close(fd) < 0)
		close_failed("close");
	return (outfile);
}

void	parse_out_util1(t_output *out, bool *out_redirection)
{
	if (!*out_redirection)
			out->kind = PIPE;
}

void	parse_out_util2(t_token *token, t_output *out, bool *out_redirection)
{
	*out_redirection = true;
	token = create_outfile(token, out);
}

void	read_till_pipe(t_token **head)
{
	t_token	*token;

	token = get_next_token(head);
	while (token)
	{
		token->is_read = true;
		if (token->kind == PIPE)
			break ;
		token = token->next;
	}
}

t_token	*parse_out_helper(t_token **head, t_token *token,
							t_output *out, bool *out_redirection)
{
	while (token)
	{
		if (token->is_read)
		{
			token = token->next;
			continue ;
		}
		token->is_read = true;
		if (token->kind == PIPE)
		{
			parse_out_util1(out, out_redirection);
			break ;
		}
		if (token->kind == REDIRECT_OUTPUT || token->kind == APPEND)
			parse_out_util2(token, out, out_redirection);
		if (!token)
		{
			read_till_pipe(head);
			break ;
		}
		token = token->next;
	}
	return (token);
}
