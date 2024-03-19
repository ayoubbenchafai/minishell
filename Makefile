CC = cc
CFLAGS =
SRC = minishell.c ft_malloc.c f.c pwd.c cd.c env.c ayoub.c
OBJ = $(SRC:.c=.o)
NAME = minishell
all : $(NAME)
%.o : %.c
	$(CC) -c $< -g -o $@ $(CFLAGS)
$(NAME) : $(OBJ)
	(cd libft && make)
	$(CC) $(SRC) libft/libft.a -lreadline -g -o minishell

clean : 
	(cd libft && make clean)
	rm -f $(OBJ)

fclean : clean
	(cd libft && make fclean)
	rm -f $(NAME)

re : fclean all