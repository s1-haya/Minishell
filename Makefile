NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror -lreadline
CFLAGS = -lreadline -fsanitize=address

SRCS_MAIN =	main.c
MAIN_DIR = srcs/main

SRCS_BUILTINS = builtins.c	\
				 cd.c \
				 echo.c \
				 pwd.c 
BUILTINS_DIR = srcs/builtins

SRCS_TOKEN = tokenize.c	\
			 token.c	\
			 token_kind.c	\
			 free_tokens.c	\
			 syntax_error.c
TOKEN_DIR = srcs/tokenize

SRCS_EXPANCION = expancion.c	\
				 expancion_utils.c
EXPANCION_DIR = srcs/expancion

SRCS_PARSE = parse.c	\
			 get_filepath.c	\
			 here_documents.c	\
			 make_command_array.c	\
			 parse_in_redirection.c	\
			 parse_output_direction.c	\
			 parse_out_helper.c
PARSE_DIR = srcs/parse

SRCS_EXECVE_COMMAND = execve_command.c	\
					  child_process.c	\
					  wait_child_process.c
EXECVE_COMMAND_DIR = srcs/execve_command

SRCS_IS_STH = is_1.c	\
			  is_2.c
IS_STH_DIR = srcs/is_something

SRCS_ERROR = handle_failures1.c	\
			 handle_failures2.c	\
			 handle_failures3.c
ERROR_DIR = srcs/error

SRCS += $(SRCS_MAIN:%.c=$(MAIN_DIR)/%.c)
SRCS += $(SRCS_BUILTINS:%.c=$(BUILTINS_DIR)/%.c)
SRCS += $(SRCS_TOKEN:%.c=$(TOKEN_DIR)/%.c)
SRCS += $(SRCS_EXPANCION:%.c=$(EXPANCION_DIR)/%.c)
SRCS += $(SRCS_PARSE:%.c=$(PARSE_DIR)/%.c)
SRCS += $(SRCS_EXECVE_COMMAND:%.c=$(EXECVE_COMMAND_DIR)/%.c)
SRCS += $(SRCS_IS_STH:%.c=$(IS_STH_DIR)/%.c)
SRCS += $(SRCS_ERROR:%.c=$(ERROR_DIR)/%.c)

OBJS = $(SRCS:%.c=%.o)
LIBFT_DIR = srcs/libft
LIBFT_AFILE = $(LIBFT_DIR)/libft.a
RM = rm -f

$(NAME):	$(OBJS)	$(LIBFT_AFILE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_AFILE) -o $(NAME)

all:	$(NAME)

$(LIBFT_AFILE):
	$(MAKE) -C $(LIBFT_DIR)

re:	fclean	all

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

bonus:	all

.PHONY: all re fclean clean bonus
