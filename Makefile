NAME = minishell
CC = cc
CFLAGS = 
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
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: clean fclean re all