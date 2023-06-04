/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 13:15:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env(char *envs)
{
	t_env	*list;
	char	**split_envs;

	list = malloc(sizeof(t_env));
	if (list == NULL)
		return (NULL);
	split_envs = ft_split(envs, '=');
	if (split_envs == NULL)
		return (NULL);
	list->name = split_envs[0];
	if (split_envs[1] == NULL && is_char_equal(envs))
		list->value = ft_strdup("");
	else
		list->value = split_envs[1];
	list->next = NULL;
	return (list);
}

t_env	*init_env(char **env)
{
	t_env	*list;
	t_env	*head;
	size_t	i;

	if (env == NULL)
		exit(EXIT_FAILURE);
	head = new_env(env[0]);
	list = head;
	i = 1;
	while (env[i])
	{
		list->next = new_env(env[i]);
		list = list->next;
		i++;
	}
	return (head);
}

// int main(int argc, char **argv, char *env[])
// {
// 	// char	*envio;
// 	char	*e;
// 	t_env	*list;

// 	list = init_env(env);
// 	while (list != NULL)
// 	{
// 		printf("name  : %s\n", list->name);
// 		printf("value : %s\n", list->value);
// 		list = list->next;
// 	}
// 	exit(0);
// 	e = *env;
// 	while (*env)
// 	{
// 		e = *env;
// 		printf("%s\n", e);
// 		env++;
// 	}
// 	return (0);
// }