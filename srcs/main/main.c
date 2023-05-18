/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:08:39 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:08:41 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell(char *line, char const *envp[])
{
	t_token	*head;

	head = NULL;
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
}

int	main(int argc, char *argv[], char const *envp[])
{
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (line)
			minishell(line, envp);
		free(line);
	}
	return (0);
}
