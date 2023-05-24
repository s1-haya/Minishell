/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:08:39 by tterao            #+#    #+#             */
/*   Updated: 2023/05/23 16:02:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_status = 0;

void	minishell(char *line, char const *envp[])
{
	t_token	*head;
	int		dupped_stdin;

	head = NULL;
	if (tokenize(&head, line))
	{
		free_tokens(&head);
		return ;
	}
	expancion(&head);
	/*
	// トークン確認用

	tokenize(&head, line);
	expancion(&head);
	t_token	*token;
	token = head;
	while (token)
	{
		builtins(token->str);
		printf("  str:%s---\n", token->str);
		printf("e str:%s---\n", token->expanded_str);
		token = token->next;
	}
	*/
	dupped_stdin = dup(STDIN_FILENO);
	if (dupped_stdin < 0)
		dup_failed("dup");
	pid_t *array = parse(&head, envp, dupped_stdin, NULL);
	if (dup2(dupped_stdin, STDIN_FILENO) < 0)
		dup2_failed("dup2");
	if (close(dupped_stdin) < 0)
		close_failed("close");
	wait_child_process(array);
	// wait_child_process(num_cmd);
	free_tokens(&head);
}

int	main(int argc, char *argv[], char const *envp[])
{
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line && !only_space(line))
			minishell(line, envp);
		free(line);
	}
	return (0);
}
