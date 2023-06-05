/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:35:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/05 13:10:48 by hsawamur         ###   ########.fr       */
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
		exit_too_many_arguments_faild(command[i]);
		return ;
	}
	printf("exit\n");
	exit(ft_atoi(command[1]));
}
