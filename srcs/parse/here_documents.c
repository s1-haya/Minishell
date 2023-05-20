/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:09:25 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 14:09:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	have_nl(const char *buff)
{
	size_t	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

char	*read_stdin(int fd)
{
	char	*str;
	char	*tmp;
	char	buff[BUFFERSIZE + 1];
	ssize_t	read_bytes;

	str = ft_strdup("");
	if (!str)
		malloc_failed("malloc");
	*buff = '\0';
	while (!have_nl(buff))
	{
		read_bytes = read(fd, buff, BUFFERSIZE);
		if (read_bytes == -1)
		{
			free(str);
			read_failed("read");
		}
		buff[read_bytes] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (!str)
			malloc_failed("malloc");
	}
	return (str);
}

char	*get_here_documents(char *delimiter)
{
	char	*here_doc;
	char	*str;
	char	*tmp;

	here_doc = ft_strdup("");
	if (!here_doc)
		malloc_failed("malloc");
	while (true)
	{
		str = read_stdin(STDIN_FILENO);
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter))
			&& ft_strlen(str) - 1 == ft_strlen(delimiter))
		{
			free(str);
			break ;
		}
		tmp = here_doc;
		here_doc = ft_strjoin(here_doc, str);
		free(tmp);
		free(str);
		if (!here_doc)
			malloc_failed("malloc");
	}
	return (here_doc);
}

t_token	*here_documents(t_token *token)
{
	char	*here_doc;
	t_token	*delimiter;
	int		pipefd[2];

	token->is_read = true;
	delimiter = token->next;
	if (!delimiter)
		return (syntax_error_str("newline"));
	here_doc = get_here_documents(delimiter->str);
	if (pipe(pipefd) < 0)
		pipe_failed("pipe");
	if (write(pipefd[W], here_doc, ft_strlen(here_doc)) < 0)
		write_failed("write");
	if (dup2(pipefd[R], STDIN_FILENO) < 0)
		dup2_failed("dup2");
	if (close(pipefd[R]) + close(pipefd[W]) < 0)
		close_failed("close");
	free(here_doc);
	delimiter->is_read = true;
	return (delimiter);
}
