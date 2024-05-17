#include "minishell.h"

int main()
{
    char **str = NULL;
   str = ft_malloc(sizeof(char *) * 3, NULL);
    str[0] = ft_malloc(sizeof(char) * 3, NULL);
    str[1] = ft_malloc(sizeof(char) * 3, NULL);
    str[0][0] = 'a';
    str[0][1] = 'b';
    str[0][2] = '\0';
    str[1][0] = 'c';
    str[1][1] = 'd';
    str[1][2] = '\0';
    str[2] = NULL;
    puts(str[0]);
    puts(str[1]);
}