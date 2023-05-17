/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_failures3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:59:54 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:59:56 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*command_not_found(char *command)
{
	printf("%s: command not found\n", command);
	return (NULL);
}

void	syntax_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
