/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:10:40 by tterao            #+#    #+#             */
/*   Updated: 2023/05/17 14:10:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../srcs/libft/libft.h"

# define BUFFERSIZE 1000


typedef	enum	e_token_kind
{
	WORD,
	PIPE, // |
	STDIN, // <
	INFILE,
	REDIRECT_OUTPUT, // >
	HEREDOC, // <<
	DELIMITER,
	HERESTRING, // <<<
	INSTRING,
	APPEND, // >>
	STDOUT,
	OUTFILE,
}	t_token_kind;

enum	e_pipefd
{
	R = 0,
	W = 1,
};

typedef struct s_token
{
	char			*str;
	char			*expanded_str;
	bool			is_read;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef struct s_env_var
{
	char	*str;
	bool	is_error;
}	t_env_var;

//tokenize
void	tokenize(t_token **head, char *line);
void	set_token_kind(t_token **head, t_token *token);
t_token	*lasttoken(t_token **head);
int		free_token(t_token *token);

//expancion
void	expancion(t_token **head);
char	*env_var_helper1(char *str, char *new_str, size_t start, size_t end);
char	*env_var_helper2(char *str, char *new_str, size_t start, size_t end);

//is_sth
bool	is_space(char c);
bool	is_redirection(char c);
bool	is_quotation_mark(char c);
bool	is_endof_env_var(char c);
bool	is_endof_str(char c);
bool	is_eoc(char c);

//error
void	malloc_failed(char *str);
void	open_failed(char *str);
void	dup_failed(char *str);
void	dup2_failed(char *str);
void	close_failed(char *str);
void	read_failed(char *str);
void	write_failed(char *str);
void	pipe_failed(char *str);
void	fork_failed(char *str);
void	execve_failed(char *str);
void	*command_not_found(char *command);
void	syntax_error(char *str);

#endif
