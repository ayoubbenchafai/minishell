NAME = minishell
CC = cc
CFLAGS = #-fsanitize=address
SRC = minishell.c ft_malloc.c f.c pwd.c cd.c env.c ayoub.c signals.c
OBJ = $(SRC:.c=.o)

LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	(cd libft && make) 
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -g -L $(LINKREADLINELIB) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -g -c $< -I $(LINKREADLINELIB1) -o $@

clean:
	(cd libft && make clean)
	rm -f $(OBJ)

fclean: clean
	(cd libft && make fclean)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all