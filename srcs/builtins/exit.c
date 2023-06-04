/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/04 13:18:35 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//bash $: exit ++
// exit 
// bash: exit: ++: numeric argument required
// 正常の場合終了ステータスは前回のまま
// 引数は数字　終了ステータスの値が入る
void	exit_mode(char **command)
{
	size_t	i;

	i = 0;
	if (command[1] == NULL)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	while (command[1][i])
	{
		if (!(ft_isdigit(command[1][i])))
			exit_not_n_faild(command[1]);
		i++;
	}
	if (arrlen(command) >= 3)
	{
		printf("exit: too many arguments\n");
		g_vars.exit_status = 1;
		return ;
	}
	printf("exit\n");
	exit(ft_atoi(command[1]));
}
