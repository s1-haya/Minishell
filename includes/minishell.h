/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:10:40 by tterao            #+#    #+#             */
/*   Updated: 2023/05/28 22:04:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
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

enum	e_exit_status
{
	COMMAND_NOT_EXECUTABLE = 126,
	COMMAND_NOT_FOUND = 127,
	SYNTAX_ERROR = 258,
};

typedef struct s_env{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*str;
	char			*expanded_str;
	bool			is_read;
	t_token_kind	kind;
	struct s_token	*next;
}	t_token;

typedef struct s_command_data
{
	char	*filepath;
	char	**command;
	t_env	*envs;
}	t_command_data;

typedef struct s_output
{
	t_token_kind	kind;
	char			*outfile;
	bool			have_pipe;
}	t_output;

extern	int	g_status;

//builtins
void	builtins(char **command,  t_env **env_val);
void	echo_mode(char **command);
void	cd_mode(char **command);
void	pwd_mode(char **command);
void	export_mode(char **command,  t_env **env_val);
void	env_mode(char **command,  t_env **env_val);
size_t	arrlen(char **arr);
t_env	*init_env(char **env);
t_env	*new_env(char *env_val);
char	**change_array(t_env *env);
void	unset_mode(char **command, t_env **env_val);

//tokenize
bool		tokenize(t_token **head, char *line);
void		set_token_kind(t_token **head, t_token *token);
int			newtoken(t_token **head, char *line, size_t start, size_t end);
void		addback(t_token **head, t_token *newtoken);
t_token		*lasttoken(t_token **head);
int			free_token(t_token *token);
void		free_tokens(t_token **head);
bool		is_syntax_error(t_token **head);
bool		is_invalid_in_value(t_token *token);
bool		is_quotation_closed(t_token **head);

//expansion
void		expansion(t_token **head, t_env *envs);
char		*expand_env_var(char *str, t_env *envs);
char		*get_env_exp_ev(char *env, t_env *envs);
char		*ft_getenv(char *target, t_env *envs);
char		*delete_quotation(char *str);

//parse
pid_t		*parse(t_token **head, t_command_data *d,
				int dupped_stdin, pid_t *array);
t_token		*get_next_token(t_token **head);
int			parse_in_redirection(t_token **head, t_env *envs, int dupped_stdin);
t_token		*here_documents(t_token *token, t_env *envs, int dupped_stdin);
char		*make_delimiter(char *str);
char		*expand_env_var_heredoc(char *str, char *delimiter,
				char *delimiter_str, t_env *envs);
char		*get_filepath(char *command);
int			get_num_wait(t_token **head);
char		**make_command_array(t_token **head);
t_output	*parse_out_redirection(t_token **head);
t_token		*parse_out_helper(t_token **head, t_token *token,
				t_output *out, bool *out_redirection);
int			read_till_pipe(t_token **head);
pid_t		*make_process_array(pid_t adding_pid, pid_t *array);

//execve_command
pid_t		execute_command(t_token **head, t_command_data *d, t_output *out);
void		child_process(t_command_data *d, t_token_kind output_direction,
				char *outfile, int *pipefd);
void		wait_child_process(pid_t *array);

//is_sth
bool		is_space(char c);
bool		is_redirection(char c);
bool		is_quotation_mark(char c);
bool		is_endof_env_var(char c);
bool		is_endof_str(char c);
bool		is_operator(char c);
bool		is_meta_character(char c);
bool		start_with(const char *str, const char *keyword);
bool		have_dollarmark(char *str);
bool		is_invalid_token(t_token *token);
bool		have_quotationmark(char *str);
bool		is_char_equal(char *str);

//error
void		malloc_failed(char *str);
void		open_failed(char *str);
void		open_failed_exit(char *str);
void		dup_failed(char *str);
void		dup2_failed(char *str);
void		close_failed(char *str);
void		read_failed(char *str);
void		write_failed(char *str);
void		pipe_failed(char *str);
void		fork_failed(char *str);
void		execve_failed(char *str);
void		wait_failed(char *str);
void		command_not_found(char *command);
void		*syntax_error_c(char c);
void		*syntax_error_str(char *str);
bool		only_space(char *str);

#endif
