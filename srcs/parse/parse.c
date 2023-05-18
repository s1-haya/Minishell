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

t_token_kind	parse_output_direction(t_token **head)
{
	t_token	*node;

	node = get_next_token(head);
	if (!node)
		return (STDOUT);
	node->is_read = true;
	// printf("output:%s %d\n", node->expanded_str, node->kind);
	return (node->kind);
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

void	free_data(t_command_data *d)
{
	size_t	i;

	i = 0;
	while (d->command && d->command[i])
	{
		free(d->command[i]);
		i++;
	}
	free(d->command);
	if (d->filepath)
		free(d->filepath);
}

void	parse(t_token **head, char const *envp[])
{
	t_command_data	d;
	int				output_direction;

	if (get_next_token(head) == NULL)
	{
		// printf("parser end\n");
		return ;
	}
	d.envp = (char **)envp;
	parse_in_redirection(head);
	d.command = make_command_array(head);
	d.filepath = get_filepath(d.command[0]);
	if (!d.filepath)
	{
		free_data(&d);
		parse_output_direction(head);
		parse(head, envp);
	}
	execute_command(head, &d, parse_output_direction(head));
	free_data(&d);
	parse(head, envp);
}
