/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:51:08 by tterao            #+#    #+#             */
/*   Updated: 2023/05/27 18:51:10 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_heredoc(char *str, t_env *envs)
{
	char	*env;

	if (!ft_strncmp(str, "$?", ft_strlen(str)) && ft_strlen(str) == 2)
	{
		env = ft_itoa(g_vars.exit_status);
		if (!env)
			malloc_failed("malloc");
		free(str);
	}
	else if (!ft_strncmp(str, "$", ft_strlen(str)) && ft_strlen(str) == 1)
		env = str;
	else
	{
		env = ft_getenv(str, envs);
		free(str);
	}
	return (env);
}

char	*env_var_heredoc_helper(char *tmp, char *heredoc, t_env *envs)
{
	char	*env;

	env = expand_heredoc(tmp, envs);
	if (!env)
		return (heredoc);
	if (!heredoc)
		return (env);
	tmp = heredoc;
	heredoc = ft_strjoin(heredoc, env);
	free(tmp);
	free(env);
	if (!heredoc)
		malloc_failed("malloc");
	return (heredoc);
}

char	*env_var_heredoc(char *str, char *heredoc, size_t *index, t_env *envs)
{
	size_t	i;
	size_t	start;
	char	*tmp;

	i = *index;
	start = i;
	if (str[i] == '?')
	{
		tmp = ft_strdup("$?");
		i++;
	}
	else
	{
		while (!is_endof_env_var(str[i]))
			i++;
		if (i == start)
			tmp = ft_strdup("$");
		else
			tmp = ft_substr(str, start, i - start);
	}
	if (!tmp)
		malloc_failed("malloc");
	*index = i;
	return (env_var_heredoc_helper(tmp, heredoc, envs));
}

char	*str_heredoc(char *str, char *heredoc, size_t *index)
{
	size_t	i;
	size_t	start;
	char	*adding_str;
	char	*tmp;

	i = *index;
	start = i;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	adding_str = ft_substr(str, start, i - start);
	if (!adding_str)
		malloc_failed("malloc");
	if (!heredoc)
		heredoc = adding_str;
	else
	{
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, adding_str);
		free(tmp);
		free(adding_str);
		if (!heredoc)
			malloc_failed("malloc");
	}
	*index = i;
	return (heredoc);
}

char	*expand_env_var_heredoc(char *str, char *delimiter,
									char *delimiter_str, t_env *envs)
{
	char	*heredoc;
	size_t	i;

	heredoc = NULL;
	if (!str || (have_quotationmark(delimiter_str) || !have_dollarmark(str)))
	{
		free(delimiter);
		return (str);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			heredoc = env_var_heredoc(str, heredoc, &i, envs);
		}
		else
			heredoc = str_heredoc(str, heredoc, &i);
	}
	free(str);
	free(delimiter);
	return (heredoc);
}
