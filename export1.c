#include "minishell.h"

int	ft_strcmp(const char *s1,const char *s2)
{
	int i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void swap(char **a, char **b)
{   
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}

// int check_error(char *var)
// {
//     int i = 0;
//     int j;
//     int size;
    
//     if (var[i] == '_')
//         i++;
//     j = i;
//     if(!ft_isalpha(var[i]))
//         return (0);
//     size = get_equal(var);
//     while(var[i] && (size == 0))
//     {
//         if(var[i]!='_')
//             if (!ft_isalnum(var[i]))
//                 return (0);
//         i++;
//     }
//     i += j;
//     while(i < size)
//     {
//         if(var[i] != '_')
//         {
//             if(var[i] == '+' && var[i + 1])
//             {
//                 i++;
//                 if(var[i] == '=')
//                     break;
//                 else 
//                     return (0);
//             }
//         if (!ft_isalnum(var[i]))
//             return (0);
//         }
//         i++;
//     }
//     return (1);
// }

int case_one(char *var, int *i, int size)
{
    while(var && var[*i] && (size == 0))
    {
        if(var[*i]!='_')
            if (!ft_isalnum(var[*i]))
                return (0);
        (*i)++;
    }
    return (1);
}

int case_two(char *var, int i, int size)
{
    while(i < size)
    {
        if(var[i] != '_')
        {
            if(var[i] == '+' && var[i + 1])
            {
                i++;
                if(var[i] == '=')
                    break;
                else 
                    return (0);
            }
            if (!ft_isalnum(var[i]))
                return (0);
        }
        i++;
    } 
    return (1);
}

int check_error(char *var)
{
    int i = 0;
    int j;
    int size;
    
    if (var[i] == '_')
        i++;
    j = i;
    if(!ft_isalnum(var[i]))
        return (0);
    size = get_equal(var);
    if (!case_one(var, &i, size))
        return (0);
    i += j;
    if(!case_two(var, i, size))
        return (0);
    return (1);
}

int get_best_size(char *var)
{
    int j = 0;
    int size = get_equal(var);
    
    if (size == 0)
        j = ft_strlen(var);
    else
    {
        if(var[size - 1] == '+' && var[size] == '=')
            j = size - 1;
        else
            j = size;
    }
    return (j);
}

int exec_env(char **env)
{
    int i;
    int j;
    
    i = 0;
    while(env && env[i])
    {
        j = 0;
        while(env[i][j])
        {
            if(env[i][j] == '+' && env[i][j + 1] == '=')
                j++;
            write(1, &env[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
    // if(i == 0)
        // new_environment();
    return 0;
}

char *expand_heredoc(char *var, char **env, t_node **addresses)
{
    int i;
    char *trim;
    char *s;

    i = 0;
    if (!check_char(var, '$'))
        return (var);
    trim = ft_strtrim(var, "$", addresses);
    
    while (env && env[i])
    {
        if (!ft_strncmp(env[i], trim, get_equal(env[i])))
        {
            s = env[i] + get_equal(env[i]) + 1;
            return (ft_strdup(s, addresses));
        }
        i++;
    }
    return (NULL);
}