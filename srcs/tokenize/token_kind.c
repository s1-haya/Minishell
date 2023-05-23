/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_kind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:05:31 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 15:05:33 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_token(t_token *token)
{
	free(token->str);
	free(token);
	return (0);
}

void	other_kinds(t_token *token)
{
	if (!ft_strncmp(token->str, "|", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen("|"))
		token->kind = PIPE;
	else if (!ft_strncmp(token->str, "<<<", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen("<<<"))
		token->kind = HERESTRING;
	else if (!ft_strncmp(token->str, "<<", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen("<<"))
		token->kind = HEREDOC;
	else if (!ft_strncmp(token->str, "<", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen("<"))
		token->kind = STDIN;
	else if (!ft_strncmp(token->str, ">>", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen(">>"))
		token->kind = APPEND;
	else if (!ft_strncmp(token->str, ">", ft_strlen(token->str))
		&& ft_strlen(token->str) == ft_strlen(">"))
		token->kind = REDIRECT_OUTPUT;
	else
		token->kind = WORD;
}

void	set_token_kind(t_token **head, t_token *token)
{
	t_token	*last_token;

	last_token = lasttoken(head);
	if (last_token && last_token->kind == STDIN)
		token->kind = INFILE;
	else if (last_token && last_token->kind == HEREDOC)
		token->kind = DELIMITER;
	else if (last_token && last_token->kind == HERESTRING)
		token->kind = INSTRING;
	else if (last_token
		&& (last_token->kind == REDIRECT_OUTPUT || last_token->kind == APPEND))
		token->kind = OUTFILE;
	else
		other_kinds(token);
}
