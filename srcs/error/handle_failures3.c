/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_failures3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:59:54 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:59:56 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_not_found(char *command)
{
	printf("%s: command not found\n", command);
	exit(COMMAND_NOT_FOUND);
}

void	*syntax_error_c(char c)
{
	printf("syntax error near unexpected token `%c'\n", c);
	g_vars.exit_status = SYNTAX_ERROR;
	return (NULL);
}

void	*syntax_error_str(char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	g_vars.exit_status = SYNTAX_ERROR;
	return (NULL);
}

void	wait_failed(char *str)
{
	perror(str);
	g_vars.exit_status = EXIT_FAILURE;
}

void	open_failed_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
