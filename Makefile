# NAME = minishell
# CC = cc
# CFLAGS =
 SRC = minishell.c ft_malloc.c f.c pwd.c cd.c env.c ayoub.c signals.c
# LINKREADLINELIB = $(shell brew --prefix readline)/lib
# LINKREADLINELIB1 = $(shell brew --prefix readline)/include
# OBJ = $(SRC:.c=.o)
# all : $(NAME)
# %.o : %.c minishell.h -I $(LINKREADLINELIB1)
# 	$(CC) -c $< -g -o $@  $(CFLAGS)
# $(NAME) : $(OBJ)
# 	(cd libft && make)
# 	$(CC) $(SRC) libft/libft.a  -L $(LINKREADLINELIB) -lreadline  -g -o minishell

# clean : 
# 	(cd libft && make clean)
# 	rm -f $(OBJ)

# fclean : clean
# 	(cd libft && make fclean)
# 	rm -f $(NAME)

# re : fclean all

NAME = minishell
CC = cc
CFLAGS = -fsanitize=address
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