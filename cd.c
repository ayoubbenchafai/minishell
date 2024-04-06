#include "minishell.h"

int exec_cd(char *path)
{
    int     response;
    char    *cwd;
    char    *new_path;
    if(path == NULL || !ft_strncmp(path, "~", 1))
    {
        response = chdir(getenv("HOME"));
        return response;
    }
    if(path[0] == '/')
    {
        response = chdir(path);
        return response;
    }
    else
    {
        cwd = getcwd(NULL, 0);
        new_path = ft_strjoin(cwd, "/");
        free(cwd);
        cwd = ft_strjoin(new_path, path);
        free(new_path);
        response = chdir(cwd);
        free(cwd);
        return response;
    }
    return 0;
}