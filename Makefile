NAME = minishell
CC = cc -fsanitize=address
CFLAGS = -g -Wall -Wextra -Werror
SRC = minishell.c heredoc.c execution.c signals.c parsing/core_parsing.c parsing/errors.c parsing/first_parse.c parsing/second_parse.c parsing/node.c \
	parsing/parsing_helpers.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/expand.c builtins/export.c builtins/pwd.c \
	builtins/unset.c ft_functions/ft_atoi.c ft_functions/ft_ft_strdup.c ft_functions/ft_ft_strjoin.c ft_functions/ft_isalnum.c ft_functions/ft_isalpha.c \
	ft_functions/ft_itoa.c  ft_functions/ft_malloc.c ft_functions/ft_memcpy.c ft_functions/ft_memmove.c ft_functions/ft_putchar_fd.c ft_functions/ft_putendl_fd.c \
	ft_functions/ft_split.c ft_functions/ft_strdup.c ft_functions/ft_strjoin.c ft_functions/ft_strlcpy.c ft_functions/ft_putstr_fd.c ft_functions/ft_strlen.c \
	ft_functions/ft_strncmp.c ft_functions/ft_strnstr.c ft_functions/ft_strtrim.c ft_functions/ft_substr.c ft_functions/utils1.c \
	ft_functions/utils2.c ft_functions/utils3.c ft_functions/utils4.c
OBJ = $(SRC:.c=.o)
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L $(LINKREADLINELIB) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS)  -c $< -I $(LINKREADLINELIB1) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean