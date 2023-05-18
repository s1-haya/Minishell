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
	int		tmp_fd;

	head = NULL;
	tokenize(&head, line);
	expancion(&head);

	// t_token	*token;
	// token = head;
	// while (token)
	// {
	// 	printf("  str:%s---\n", token->str);
	// 	printf("e str:%s---\n", token->expanded_str);
	// 	token = token->next;
	// }
	tmp_fd = dup(STDIN_FILENO);
	if (tmp_fd < 0)
		dup_failed("dup");
	parse(&head, envp);
	if (dup2(tmp_fd, STDIN_FILENO) < 0)
		dup2_failed("dup2");
	wait_child_process(&head);
	free_tokens(&head);
}

g_status = 0;

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
