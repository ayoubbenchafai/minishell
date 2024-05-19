NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = minishell.c ft_functions/ft_malloc.c node.c pwd.c cd.c env.c  signals.c ft_functions/ft_strjoin.c ft_functions/ft_strncmp.c \
    ft_functions/ft_split.c ft_functions/ft_strlen.c ft_functions/ft_strdup.c ft_functions/ft_memcpy.c ft_functions/ft_memmove.c \
	ft_functions/ft_putstr_fd.c ft_functions/ft_strlcpy.c ft_functions/ft_strnstr.c ft_functions/ft_isalpha.c ft_functions/ft_isalnum.c \
	export.c ft_functions/ft_substr.c ft_functions/ft_putchar_fd.c ft_functions/ft_putendl_fd.c ft_functions/ft_itoa.c \
	ft_functions/ft_atoi.c exit.c echo.c unset.c ft_functions/ft_ft_strdup.c ft_functions/ft_ft_strjoin.c ft_functions/ft_strtrim.c \
	expand.c utils1.c utils2.c utils3.c utils4.c heredoc.c errors.c parse1.c parse2.c execution.c core_parsing.c parsing_helpers.c
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

.PHONY: clean fclean re all