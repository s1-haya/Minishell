/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:12:25 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 20:12:26 by tterao           ###   ########.fr       */
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

int	parse(t_token **head, char const *envp[], int dupped_stdin)
{
	t_command_data	d;
	int				num_cmd;

	num_cmd = 0;
	// printf("parser\n");
	if (get_next_token(head) == NULL)
	{
		// printf("parser end\n");
		return (num_cmd);
	}
	d.envp = (char **)envp;
	if (parse_in_redirection(head, dupped_stdin))
		return (parse(head, envp, dupped_stdin));
	d.command = make_command_array(head);
	d.filepath = get_filepath(d.command[0]);
	// printf("%s\n", d.command[0]);
	// printf("%s\n", d.filepath);
	// if (!d.command[0] && !d.filepath)
	// 	return (free_data(&d));
	execute_command(head, &d, parse_out_redirection(head));
	num_cmd += free_data(&d);
	num_cmd += parse(head, envp, dupped_stdin);
	return (num_cmd);
}
