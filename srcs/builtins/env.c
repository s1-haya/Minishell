/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:18:13 by hsawamur          #+#    #+#             */
/*   Updated: 2023/05/28 21:38:26 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_mode(char **command, t_env **env_val)
{
	t_env	*ite;
	size_t	i;

	if (command[1] == NULL)
	{
		ite = *env_val;
		while(ite != NULL)
		{
			if (ft_strcmp(ite->name, "_"))
				printf("%s=%s\n", ite->name, ite->value);
			ite = ite->next;
		}
	}
}
