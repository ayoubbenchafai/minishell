CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCM = ft_strlcpy.c ft_toupper.c ft_atoi.c ft_memchr.c ft_strlen.c ft_isascii.c ft_bzero.c ft_memcmp.c ft_split.c ft_strncmp.c ft_calloc.c ft_memcpy.c ft_strchr.c ft_strnstr.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c \
	ft_isalnum.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_isalpha.c ft_memset.c ft_strtrim.c ft_isdigit.c ft_strjoin.c ft_substr.c ft_isprint.c ft_strlcat.c ft_tolower.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c
SRCB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJM = $(SRCM:.c=.o)
OBJB = $(SRCB:.c=.o)
NAME = libft.a

%.o:%.c libft.h
	$(CC) $(CFLAGS) -c -g $< -o $@

all : $(NAME)

$(NAME) : $(OBJM)
	ar -rc  $(NAME) $(OBJM)

bonus : $(NAME) $(OBJB)
	ar -rc $(NAME) $(OBJB)

clean :
	rm -f $(OBJM) $(OBJB)

fclean : clean
	rm -f $(NAME)

re : fclean all