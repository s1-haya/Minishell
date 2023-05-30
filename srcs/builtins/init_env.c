/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:44:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/28 22:14:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env(char *env_val)
{
	t_env	*list;
	char	**split_env_val;

	list = malloc(sizeof(t_env));
	if (list == NULL)
		return (NULL);
	split_env_val = ft_split(env_val, '=');
	if (split_env_val == NULL)
		return (NULL);
	list->name = split_env_val[0];
	if (split_env_val[1] == NULL && is_char_equal(env_val))
		list->value = ft_strdup("");
	else
		list->value = split_env_val[1];
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
		// printf("env   %s\n", env[i]);
		list->next = new_env(env[i]);
		// printf("list name  %s\n", list->name);
		// printf("list value %s\n", list->value);
		list = list->next;
		i++;
	}
	// printf("head name   %s\n", head->name);
	// printf("head value   %s\n", head->value);
	// exit(0);
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