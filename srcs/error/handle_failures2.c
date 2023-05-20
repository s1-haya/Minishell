/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_failures2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:58:32 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:58:33 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_failed(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	dup2_failed(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	pipe_failed(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	fork_failed(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	execve_failed(char *str)
{
	perror(str);
	g_status = COMMAND_NOT_EXECUTABLE;
}
