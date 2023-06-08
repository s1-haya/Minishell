/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:56:40 by tterao            #+#    #+#             */
/*   Updated: 2023/05/29 17:56:41 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_var_helper(char *env, char *expanded_str, t_env *envs)
{
	char	*tmp;

	env = get_env_exp_ev(env, envs);
	if (!env)
		return (expanded_str);
	if (!expanded_str)
		return (env);
	tmp = expanded_str;
	expanded_str = ft_strjoin(tmp, env);
	free(tmp);
	free(env);
	if (!expanded_str)
		malloc_failed("malloc");
	return (expanded_str);
}

char	*env_var(char *str, char *expanded_str, t_env *envs, size_t *index)
{
	char	*env;
	size_t	i;
	size_t	start;

	i = *index;
	start = i;
	if (str[i] == '?')
	{
		env = ft_strdup("$?");
		i++;
	}
	else
	{
		while (!is_endof_env_var(str[i]))
			i++;
		if (i == start)
			env = ft_strdup("$");
		else
			env = ft_substr(str, start, i - start);
		if (!env)
			malloc_failed("malloc");
	}
	*index = i;
	return (env_var_helper(env, expanded_str, envs));
}

char	*substr_exp_ev(char *str, char *expanded_str, size_t start, size_t end)
{
	char	*adding_str;
	char	*tmp;

	if (start == end)
		return (expanded_str);
	adding_str = ft_substr(str, start, end - start);
	if (!adding_str)
		malloc_failed("malloc");
	if (!expanded_str)
		return (adding_str);
	tmp = expanded_str;
	expanded_str = ft_strjoin(expanded_str, adding_str);
	free(adding_str);
	free(tmp);
	if (!expanded_str)
		malloc_failed("malloc");
	return (expanded_str);
}

void	*init_vars_exp_ev(size_t *i, size_t *start, bool *s_quotation)
{
	*i = 0;
	*start = 0;
	*s_quotation = false;
	return (NULL);
}

char	*expand_env_var(char *str, t_env *envs)
{
	char	*expanded_str;
	size_t	i;
	size_t	start;
	bool	s_quotation;

	expanded_str = init_vars_exp_ev(&i, &start, &s_quotation);
	while (str[i])
	{
		if (str[i] == '\'')
			s_quotation = !s_quotation;
		if (str[i] == '$' && !s_quotation)
		{
			expanded_str = substr_exp_ev(str, expanded_str, start, i);
			i++;
			if (is_quotation_mark(str[i]))
				;
			else
				expanded_str = env_var(str, expanded_str, envs, &i);
			start = i;
		}
		else
			i++;
	}
	return (substr_exp_ev(str, expanded_str, start, i));
}
