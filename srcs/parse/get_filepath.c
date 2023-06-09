/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filepath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:26:19 by tterao            #+#    #+#             */
/*   Updated: 2023/06/07 18:39:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_dirs(char **dirs)
{
	size_t	i;

	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (NULL);
}

bool	is_dir(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

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
		if (access(filepath, X_OK) == 0 && !is_dir(filepath))
		{
			free_dirs(dirs);
			return (filepath);
		}
		free(filepath);
	}
	free_dirs(dirs);
	return (NULL);
}

char	*get_filepath(char *command, t_env *envs)
{
	char		*path;
	char		**dirs;

	if (!command || command[0] == '\0')
		return (NULL);
	if (access(command, X_OK) == 0 && !is_dir(command))
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
	free(path);
	if (!dirs)
		malloc_failed("malloc");
	return (make_filepath(dirs, command));
}
