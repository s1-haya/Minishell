/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:17:36 by tterao            #+#    #+#             */
/*   Updated: 2023/06/05 15:17:37 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_heredoc_vars(char *buff)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		malloc_failed("malloc");
	*buff = '\0';
	return (str);
}

char	*handle_signal(char *str, char *buff)
{
	if (g_vars.sig_no == SIGINT || *buff == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*sig_action_heredoc(char *str, char *here_doc)
{
	if (!str)
	{
		free(here_doc);
		return (NULL);
	}
	return (here_doc);
}
