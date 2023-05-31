/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:26:19 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 14:26:20 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_filepath(char **dirs, char *command)
{
	size_t	i;
	char	*filepath;
	char	*tmp;

	i = 0;
	while (dirs[i])
	{
		filepath = ft_strjoin(dirs[i++], "/");
		if (!filepath)
			malloc_failed("malloc");
		tmp = filepath;
		filepath = ft_strjoin(filepath, command);
		free(tmp);
		if (!filepath)
			malloc_failed("malloc");
		if (access(filepath, X_OK) == 0)
		{
			free(dirs);
			return (filepath);
		}
		free(filepath);
	}
	free(dirs);
	return (NULL);
}

char	*get_filepath(char *command, t_env *envs)
{
	char	*path;
	char	*tmp;
	char	**dirs;
	size_t	i;

	if (!command || command[0] == '\0')
		return (NULL);
	if (access(command, X_OK) == 0)
	{
		path = ft_strdup(command);
		if (!path)
			malloc_failed("malloc");
		return (path);
	}
	path = ft_getenv("PATH", envs);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		malloc_failed("malloc");
	return (make_filepath(dirs, command));
}
