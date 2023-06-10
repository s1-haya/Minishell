/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:57:25 by tterao            #+#    #+#             */
/*   Updated: 2023/06/10 14:57:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	not_directory(char *str)
{
	const char	*message = ": Not a directory\n";

	printf("%s%s", str, message);
	exit(COMMAND_NOT_EXECUTABLE);
}

void	is_directory(char *str)
{
	const char	*message = ": is a directory\n";

	printf("%s%s", str, message);
	exit(COMMAND_NOT_EXECUTABLE);
}

bool	is_file(char *str)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = pwd;
	pwd = ft_strjoin(pwd, "/");
	free(tmp);
	if (!pwd)
		malloc_failed("malloc");
	tmp = pwd;
	pwd = ft_strjoin(pwd, str);
	if (!pwd)
		malloc_failed("malloc");
	if (access(pwd, F_OK) == 0)
	{
		free(pwd);
		return (true);
	}
	free(pwd);
	return (false);
}

void	handle_file_dir(char *str)
{
	struct stat	statbuf;

	if (stat(str, &statbuf) == 0)
		is_directory(str);
	else if (is_file(str))
		not_directory(str);
	else
	{
		printf("%s: No such file or directory\n", str);
		exit(COMMAND_NOT_FOUND);
	}
}
