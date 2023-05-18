/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:42 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:37:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_end_index_helper(char *line, size_t i)
{
	if (line[i] == '|')
	{
		while (line[i] == '|' && line[i] != '\0')
			i++;
	}
	else
	{
		while (!is_space(line[i]) && !is_quotation_mark(line[i])
			&& line[i] != '|' && line[i] != '\0')
			i++;
	}
	return (i);
}

size_t	get_end_index(char *line, size_t i)
{
	char	c;

	if (is_quotation_mark(line[i]))
	{
		c = line[i++];
		while (line[i] != c && line[i] != '\0')
			i++;
		if (line[i] != '\0')
			i++;
	}
	else if (is_redirection(line[i]))
	{
		c = line[i];
		while (line[i] == c && line[i] != '\0')
			i++;
	}
	else if (line[i] == '|')
	{
		while (line[i] == '|' && line[i] != '\0')
			i++;
	}
	else
		i = get_end_index_helper(line, i);
	return (i);
}

void	tokenize(t_token **head, char *line)
{
	t_token	*token;
	size_t	i;
	size_t	start;

	i = 0;
	while (line[i])
	{
		while (is_space(line[i]) && line[i] != '\0')
			i++;
		start = i;
		i = get_end_index(line, i);
		if (newtoken(head, line, start, i))
			break ;
	}
}
