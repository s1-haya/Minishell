/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:42 by tterao            #+#    #+#             */
/*   Updated: 2023/06/07 18:39:37 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_end_index_helper(char *line, size_t i)
{
	while (!is_space(line[i]) && !is_quotation_mark(line[i])
		&& !is_meta_character(line[i]) && line[i] != '\0')
		i++;
	return (i);
}

size_t	get_end_index(char *line, size_t i)
{
	char	c;

	if (is_operator(line[i]))
	{
		c = line[i];
		while (line[i] == c && line[i] != '\0')
			i++;
		return (i);
	}
	while (!is_meta_character(line[i]) && line[i] != '\0')
	{
		if (is_quotation_mark(line[i]))
		{
			c = line[i++];
			while (line[i] != c && line[i] != '\0')
				i++;
			if (line[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	return (i);
}

bool	tokenize(t_token **head, char *line)
{
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
	return (is_syntax_error(head));
}
