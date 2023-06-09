/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:57:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/09 15:00:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	envlast(t_env *env, t_env **p, t_env *new_env, bool sign_char_equal)
{
	*p = env;
	while (*p)
	{
		if (ft_strcmp((*p)->name, new_env->name) == 0)
		{
			if (new_env->value)
			{
				free((*p)->value);
				(*p)->value = new_env->value;
			}
			else if (sign_char_equal)
			{
				free((*p)->value);
				(*p)->value = "";
			}
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
	{
		free(new_env->name);
		free(new_env->next);
		free(new_env);
		return ;
	}
	if (p)
	{
		p->next = new_env;
		new_env->next = NULL;
	}
	else
		*env = new_env;
}

static void	export_util_mode(char **command, t_env **envs)
{
	size_t	i;
	t_env	*ite;
	bool	sign_char_equal;

	i = 1;
	while (command[i])
	{
		sign_char_equal = is_char_equal(command[i]);
		ite = new_env(command[i]);
		if (!ite || !ft_isalpha(ite->name[0]))
		{
			printf("export: `%s': not a valid identifier\n", command[i]);
			g_vars.exit_status = 1;
			if (ite != NULL)
				env_free(ite);
		}
		else
			envadd_back(envs, ite, sign_char_equal);
		i++;
	}
}

void	export_mode(char **command, t_env **envs)
{
	t_env	*ite;

	ite = *envs;
	if (command[1] == NULL)
	{
		while (ite != NULL)
		{
			if (ft_strcmp(ite->name, "_"))
			{
				if (ite->value != NULL)
					printf("declare -x %s=\"%s\"\n", ite->name, ite->value);
				else
					printf("declare -x %s\n", ite->name);
			}
			ite = ite->next;
		}
	}
	g_vars.exit_status = 0;
	export_util_mode(command, envs);
}
