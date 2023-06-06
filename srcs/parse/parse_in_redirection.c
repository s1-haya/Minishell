/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:02:42 by tterao            #+#    #+#             */
/*   Updated: 2023/06/06 10:47:18 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*here_strings(t_token *token)
{
	t_token	*word;
	char	*tmp;
	int		pipefd[2];

	token->is_read = true;
	word = token->next;
	if (pipe(pipefd) < 0)
		pipe_failed("pipe");
	tmp = word->expanded_str;
	word->expanded_str = ft_strjoin(word->expanded_str, "\n");
	free(tmp);
	if (!word->expanded_str)
		malloc_failed("malloc");
	if (write(pipefd[W], word->expanded_str, ft_strlen(word->expanded_str)) < 0)
		write_failed("write");
	if (dup2(pipefd[R], STDIN_FILENO) < 0)
		dup2_failed("dup2");
	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	word->is_read = true;
	// printf("word       %p\n", word);
	// printf("word env   %p\n", token);
	// printf("word expan %p\n", word->expanded_str);
	return (word);
}

t_token	*redirect_stdin(t_token *token)
{
	int		fd;
	t_token	*infile;

	token->is_read = true;
	infile = token->next;
	// printf("infile:%s\n", infile->expanded_str);
	infile->is_read = true;
	fd = open(infile->expanded_str, O_RDONLY);
	if (fd < 0)
	{
		open_failed(infile->expanded_str);
		return (NULL);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
		close_failed("close");
	return (infile);
}

int	parse_in_redirection(t_token **head, t_env *envs, int dupped_stdin)
{
	t_token	*token;

	token = get_next_token(head);
	while (token)
	{
		// printf("token: %s\n", token->expanded_str);
		// printf(" kind: %d\n", token->kind);
		if (token->kind == STDIN)
			token = redirect_stdin(token);
		if (!token)
			return (read_till_pipe(head));
		else if (token->kind == HEREDOC)
			token = here_documents(token, envs, dupped_stdin);
		if (!token)
			return (2);
		else if (token->kind == HERESTRING)
			token = here_strings(token);
		else if (token->kind == PIPE)
			break ;
		else
			token = token->next;
	}
	return (0);
	// printf("token end%p\n", token);
}
