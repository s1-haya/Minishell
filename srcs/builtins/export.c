/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:57:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/28 18:38:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_env_valid(char *new_env)
{
	size_t	i;

	i = 0;
	while (new_env[i])
	{
		if (!ft_isalpha(new_env[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	envlast(t_env *env, t_env **p, t_env *new_env, bool sign_char_equal)
{
	*p = env;
	while (*p)
	{
		if (ft_strcmp((*p)->name, new_env->name) == 0)
		{
			if (new_env->value)
				(*p)->value = new_env->value;
			else if (sign_char_equal)
				(*p)->value = "";
			else
			{
			}
			return (false);
		}
		if (!(*p)->next)
			break ;
		(*p) = (*p)->next;
	}
	return (true);
}

static void	envadd_back(t_env **env, t_env *new_env, bool sign_char_equal)
{
	t_env	*p;

	if (!env || !new_env)
		return ;
	if (!envlast(*env, &p, new_env, sign_char_equal))
		return ;
	if (p)
		p->next = new_env;
	else
	{
		*env = new_env;
	}
}

static void	export_util_mode(char **command, t_env **env_val)
{
	size_t	i;
	t_env	*ite;
	bool	sign_char_equal;

	i = 1;
	while (command[i])
	{
		sign_char_equal = is_char_equal(command[i]);
		ite = new_env(command[i]);
		if (!check_env_valid(ite->name))
			printf("bash: export: `%s': not a valid identifier\n", command[i]);
		else
			envadd_back(env_val, ite, sign_char_equal);
		i++;
	}
}

void	export_mode(char **command, t_env **env_val)
{
	t_env	*ite;
	size_t	i;

	ite = *env_val;
	if (command[1] == NULL)
	{
		while(ite != NULL)
		{
			if (ite->value != NULL)
				printf("declare -x %s=\"%s\"\n", ite->name, ite->value);
			else
				printf("declare -x %s\n", ite->name);
			ite = ite->next;
		}
	}
	export_util_mode(command, env_val);
}
