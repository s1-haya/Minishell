/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:36:24 by tterao            #+#    #+#             */
/*   Updated: 2023/05/18 19:36:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_child_process(t_token **head)
{
	int		num_wait;

	num_wait = get_num_wait(head);
	while (num_wait--)
	{
		if (wait(&g_status) < 0)
			wait_failed("wait");
	}
}
