#include "minishell.h"

int exec_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_putstr_fd("pwd: ", 1);
        ft_putstr_fd("\n", 1);
	    exit_status(127);
        return (0);
    }
    ft_putstr_fd(pwd, 1);
    ft_putstr_fd("\n", 1);
    free(pwd);
	exit_status(0);
    return (1);
}