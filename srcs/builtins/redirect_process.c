/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:23:04 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/08 13:42:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	redirect_output_process(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
	{
		open_failed(outfile);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
	{
		close_failed("close");
		return (false);
	}
	return (true);
}

bool	append_process(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd < 0)
	{
		open_failed(outfile);
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		dup2_failed("dup2");
	if (close(fd) < 0)
	{
		close_failed("close");
		return (false);
	}
	return (true);
}

bool	redirect_process(t_output *out)
{
	bool	is_redirect;

	is_redirect = true;
	if (out == NULL)
		is_redirect = false;
	else if (out->kind == REDIRECT_OUTPUT)
		is_redirect = redirect_output_process(out->outfile);
	else if (out->kind == APPEND)
		is_redirect = append_process(out->outfile);
	free(out);
	return (is_redirect);
}
