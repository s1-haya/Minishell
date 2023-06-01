/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_failures1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:29 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:56:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_failed(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	open_failed(char *str)
{
	perror(str);
	g_vars.exit_status = 1;
}

void	close_failed(char *str)
{
	perror(str);
	g_vars.exit_status = 1;
}

void	read_failed(char *str)
{
	perror(str);
	g_vars.exit_status = 1;
}

void	write_failed(char *str)
{
	perror(str);
	g_vars.exit_status = 1;
}
