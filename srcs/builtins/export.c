/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:57:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/26 16:57:07 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_mode(char **command, t_env **env_val)
{
	t_env	*ite;
	size_t	i;

	ite = *env_val;
	i = 0;
	// printf("declare -x %s=\"%s\"\n", ite->name, ite->value);
	// exit(0);
	while(ite->next != NULL)
	{
		if (ite->value)
			printf("declare -x %s=\"%s\"\n", ite->name, ite->value);
		ite = ite->next;
	}
	// if (arrlen(command) == 2)
	// {
	// 	*env = command[1];
	// 	printf("%s\n", *env);
	// }
}
