NAME = minishell
CC = cc
CFLAGS =  -fsanitize=address

SRC = minishell.c f_utils.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	(cd libft && make) 
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -g -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: clean fclean re all