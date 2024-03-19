#include "minishell.h"

// void free_array(char **array)
// {
//     int i;

//     i = 0;
//     if (!array)
//         return;
//     while (array[i])
//     {
//         free(array[i]);
//         i++;
//     }
//     free(array);
// }
// char **array_append(char **array, char *s, t_node **addresses)
// {
//     char **new;
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     if (!array)
//     {
//         new = (char **)malloc(sizeof(char *) * 2);
//         // ft_malloc(sizeof(char *) * 2, (void **)&new, addresses);
//         new[0] = s;
//         new[1] = NULL;
//         return new;
//     }
//     else
//     {
//         while (array[i])
//             i++;
//         new = (char **)malloc(sizeof(char *) * (i + 2));
//         // ft_malloc(sizeof(char *) * (i + 2), (void **)&new, addresses);
//     }
//     while (array[j])
//     {
//         new[j] = ft_strdup(array[j]);
//         j++;
//     }
//     new[j] = s;
//     new[j + 1] = NULL;
//     return new;
// }


// char **ft_array_remove(char **array, char *s, t_node **addresses)
// {
//     int i;
//     int j;
//     char **new;

//     i = 0;
//     j = 0;
//     if (!array)
//         return (NULL);
//     while (array[i])
//         i++;
//     // ft_malloc(sizeof(char *) * (i + 1), (void **)&new, addresses);
//     new = (char **)malloc(sizeof(char *) * (i + 1));
//     if (!new)
//         return (NULL);
//     i = 0;
//     while (array[i])
//     {
//         if (ft_strncmp(array[i], s, get_equal(s)))
//         {
//             new[j] = ft_strdup(array[i]);
//             j++;
//         }
//         i++;
//     }
//     new[j] = NULL;
//     return new;
// }

void array_to_list(t_node **lst, char **array, t_node **addresses)
{
    int i;

    i = 0;
    while (array[i])
    {
        ft_lstadd_back1(lst, ft_lstnew1(array[i], "var", addresses));
        i++;
    }
}

//hadi bach n executiw env
int exec_env(t_node *env)
{
    t_node *tmp;
    tmp = env;
    while(tmp)
    {
        ft_putstr_fd((char *)tmp->value, 1);
        ft_putstr_fd("\n", 1);
        tmp = tmp->next;
    }
    return 0;
}

// hadi bach n addiw wa7ed lvar
void put_env(t_node **env, char *var, t_node **addresses)
{
    t_node *tmp;
    tmp = *env;
    int equal_index;
    while(tmp)
    {
        equal_index = get_equal(var);   
        if(equal_index == 0)
            return ;
        if(!ft_strncmp(tmp->value, var, equal_index))
        {
            free(tmp->value);
            tmp->value = ft_strdup(var);
            return ;
        }
        tmp = tmp->next;
    }
    ft_lstadd_back1(env, ft_lstnew1(var, "var", addresses));
    return ;
}
// hadi bach n unsetiw wa7ed lvar
int get_equal(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '=')
            return i;
        i++;
    }
    return 0;
}

void unset_env(t_node **env, char *var)
{
    t_node *tmp;
    t_node *prev;
    tmp = *env;
    prev = NULL;

    while(tmp)
    {
        if(!ft_strncmp(tmp->value, var, get_equal(tmp->value)))
        {
            if(prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return ;
}
int check_char(char *s,char c)
{
    if(!s)
        return 0;
    while(*s)
    {
        if(*s == c)
            return 1;
        s++;
    
    }
    return (0);
}
int expand(char *var, t_node *env)
{
    t_node *tmp;
    tmp = env;

    if (!check_char(var, '$'))
        return (0);
    while (tmp)
    {
        if (!ft_strncmp(tmp->value, var + 1, get_equal(tmp->value)))
        {
            ft_putstr_fd(tmp->value + strlen(var), 1);
            ft_putstr_fd("\n", 1);
            return (1);
        }
        tmp = tmp->next;
    }
    return 0;
}
