NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror -lreadline
CFLAGS = -lreadline -fsanitize=address

SRCS_MAIN =	main.c
MAIN_DIR = srcs/main

SRCS_BUILTINS = builtins.c	
BUILTINS_DIR = srcs/builtins

SRCS_TOKEN = tokenize.c	\
			 token_kind.c
TOKEN_DIR = srcs/tokenize

SRCS_EXPANCION = expancion.c	\
				 expancion_utils.c
EXPANCION_DIR = srcs/expancion

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
