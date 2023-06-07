/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_failures4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:28:52 by tterao            #+#    #+#             */
/*   Updated: 2023/06/05 13:11:44 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

void	sigaction_failed(char *str)
{
	perror(str);
	g_vars.exit_status = EXIT_FAILURE;
}

void	exit_n_faild(char *str)
{
	printf("exit\n");
	printf("exit: %s: numeric argument required\n", str);
	exit(NUMERIC_ARGUMENT_REQUIRED);
}

void	exit_too_many_arguments_faild(char *str)
{
	printf("exit: too many arguments\n");
	g_vars.exit_status = NUMERIC_ARGUMENT_REQUIRED;
}

void	cd_faild(char *str)
{
	if (errno == EACCES)
		printf("cd: %s: Permission denied\n", str);
	else
		printf("cd: %s: No such file or directory\n", str);
	g_vars.exit_status = 1;
}
