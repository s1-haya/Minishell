/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:12:25 by tterao            #+#    #+#             */
/*   Updated: 2023/05/30 20:00:25 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_next_token(t_token **head)
{
	t_token	*node;

	node = *head;
	while (node)
	{
		if (!node->is_read)
			break ;
		node = node->next;
	}
	return (node);
}

int	get_num_wait(t_token **head)
{
	t_token	*token;
	int		num_wait;

	token = *head;
	num_wait = 1;
	while (token)
	{
		if (token->kind == PIPE)
			num_wait++;
		token = token->next;
	}
	return (num_wait);
}

int	free_data(t_command_data *d)
{
	size_t	i;

	i = 0;
	while (d->command[i])
	{
		free(d->command[i]);
		i++;
	}
	free(d->command);
	if (d->filepath)
		free(d->filepath);
	return (1);
}

t_token_kind	parse_output_direction(t_token **head)
{
	t_token	*token;

	token = get_next_token(head);
	if (!token)
		return (STDOUT);
	return (token->kind);
}

pid_t	*parse(t_token **head, t_command_data *d, int dupped_stdin, pid_t *array)
{
	pid_t		pid;
	t_output	*output;

	if (get_next_token(head) == NULL)
		return (array);
	if (parse_in_redirection(head, dupped_stdin))
		return (parse(head, d, dupped_stdin, array));
	d->command = make_command_array(head);
	d->filepath = get_filepath(d->command[0]);
	// printf("%s\n", d.command[0]);
	// printf("%s\n", d.filepath);
	output = parse_out_redirection(head);
	if (output->have_pipe == false && array == NULL && \
	is_builtin((d->command)[0]))
		builtins(d->command, &(d->envs));
	else
		pid = execute_command(head, d, output);
	// printf("builtin %s\n", (d->command)[0]);
	// printf("builtin %s\n", (d->command)[0]);
	free_data(d);
	return (parse(head, d, dupped_stdin, make_process_array(pid, array)));
}
