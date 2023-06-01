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

size_t	get_array_size(pid_t *array)
{
	size_t	size;

	size = 0;
	while (array[size] != -1)
		size++;
	size = size + 2;
	return (size);
}

pid_t	*malloc_process_array(pid_t adding_pid,
							pid_t *old_array, pid_t *new_array)
{
	pid_t	*array;
	size_t	i;

	i = 0;
	while (true)
	{
		if (old_array[i] == -1)
		{
			new_array[i] = adding_pid;
			i++;
			break ;
		}
		new_array[i] = old_array[i];
		i++;
	}
	new_array[i] = -1;
	free(old_array);
	return (new_array);
}

pid_t	*make_process_array(pid_t adding_pid, pid_t *array)
{
	pid_t	*new_array;
	size_t	size;

	if (!array)
	{
		new_array = malloc(sizeof(pid_t) * 2);
		if (!new_array)
			malloc_failed("malloc");
		new_array[0] = adding_pid;
		new_array[1] = -1;
		return (new_array);
	}
	new_array = malloc(sizeof(pid_t) * get_array_size(array));
	if (!new_array)
		malloc_failed("malloc");
	return (malloc_process_array(adding_pid, array, new_array));
}

void	wait_child_process(pid_t *array)
{
	int		status;
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != -1)
	{
		// printf("waitpid:%d\n",array[i]);
		if (waitpid(array[i], &status, WCONTINUED) < 0)
			wait_failed("waitpid");
		g_vars.exit_status = WEXITSTATUS(status);
		i++;
	}
	// printf("lastwaitpid:%d\n",array[i]);
	free(array);
}

// void	wait_child_process(int num_cmd)
// {
// 	int	status;

// 	// printf("num_wait:%d\n", num_wait);
// 	while (num_cmd--)
// 	{
// 		if (wait(&status) < 0)
// 			wait_failed("wait");
// 		g_vars.exit_status = WEXITSTATUS(status);
// 	}
// }
