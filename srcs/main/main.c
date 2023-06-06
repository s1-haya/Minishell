/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:08:39 by tterao            #+#    #+#             */
/*   Updated: 2023/06/05 14:55:32 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_g_vars	g_vars = {0, 0};

void	minishell(char *line, t_command_data *d)
{
	t_token	*head;
	int		dupped_stdin;
	pid_t	*array;

	head = NULL;
	if (tokenize(&head, line))
	{
		free_tokens(&head);
		return ;
	}
	expansion(&head, d->envs);
	/*
	// トークン確認用

	tokenize(&head, line);
	expansion(&head, d->envs);

	t_token	*token;
	token = head;
	while (token)
	{
		printf("  str:%s---\n", token->str);
		printf("e str:%s---\n", token->expanded_str);
		printf("kind :%d---\n", token->kind);
		token = token->next;
	}
	*/
	// /*
	dupped_stdin = dup(STDIN_FILENO);
	if (dupped_stdin < 0)
		dup_failed("dup");
	array = parse(&head, d, dupped_stdin, NULL);
	if (dup2(dupped_stdin, STDIN_FILENO) < 0)
		dup2_failed("dup2");
	if (close(dupped_stdin) < 0)
		close_failed("close");
	wait_child_process(array);
	free_tokens(&head);
	// */
}

int	main(int argc, char *argv[], char const *envp[])
{
	char			*line;
	t_command_data	d;

	d.envs = init_env((char **)envp);
	while (true)
	{
		ft_signal(PARENT);
		line = readline("minishell$ ");
		handle_eof(line);
		if (line && !only_space(line))
		{
			minishell(line, &(d));
			add_history(line);
		}
		free(line);
	}
	return (0);
}
