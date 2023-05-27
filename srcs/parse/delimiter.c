/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:44:33 by tterao            #+#    #+#             */
/*   Updated: 2023/05/27 13:44:34 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_delimiter(char *str, char *delimiter, size_t start, size_t end)
{
	char	*adding_str;
	char	*new_delimiter;

	printf("%zu %zu\n", start, end);
	if (end == start)
		adding_str = ft_strdup("");
	else
		adding_str = ft_substr(str, start, end - start);
	if (!adding_str)
		malloc_failed("malloc");
	new_delimiter = ft_strjoin(delimiter, adding_str);
	free(delimiter);
	free(adding_str);
	if (!new_delimiter)
		malloc_failed("malloc");
	return (new_delimiter);
}

char	*init_del_vars(size_t *i, size_t *start, bool *quotation)
{
	char	*delimiter;

	*i = 0;
	*start = 0;
	*quotation = false;
	delimiter = ft_strdup("");
	if (!delimiter)
		malloc_failed("malloc");
	return (delimiter);
}

void	reset_del_vars(size_t *start, size_t *i, bool *quotation)
{
	*start = *i;
	*quotation = !quotation;
}

char	*make_delimiter(char *str)
{
	size_t	i;
	size_t	start;
	char	*delimiter;
	char	target;
	bool	quotation;

	delimiter = init_del_vars(&i, &start, &quotation);
	while (str[i])
	{
		if (quotation && str[i] == target)
		{
			delimiter = join_delimiter(str, delimiter, start, i++);
			reset_del_vars(&start, &i, &quotation);
		}
		else if (is_quotation_mark(str[i]) && !quotation)
		{
			delimiter = join_delimiter(str, delimiter, start, i);
			target = str[i++];
			reset_del_vars(&start, &i, &quotation);
		}
		else
			i++;
	}
	return (join_delimiter(str, delimiter, start, i));
}
