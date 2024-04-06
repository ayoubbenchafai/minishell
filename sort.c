/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:15:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/04 03:09:03 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"

void swap(char **a, char **b)
{   
    char *c;
    c = *a;
    *a = *b;
    *b = c;
}
char **get_env(char **env)
{
    int i = 0;
    char **array;

    while(env && env[i])
        i++;
    array = (char **)malloc((sizeof(char *) * (i + 1)));
    if(!array)
        return NULL;
    i = 0;
    while(env && env[i])
    {
        array[i] = ft_strdup(env[i]);
        i++;
    }
    array[i] = NULL;
    return (array);
}

char  **get_env_export(char **env)
{
    int i = 0;
    char **array;
    
    while(env && env[i])
        i++;
    array = (char **)malloc(sizeof(char *) * (i + 1));
    if (!array)
        return NULL;
    i = 0;
    while(env && env[i])
    {
        array[i] = ft_strjoin("declare -x ", ft_strdup(env[i]));
        i++;
    }
    array[i] = NULL;
    return (array);       
}
// void set_export(char *var, char **env)
// {
//     int i;
//     i = 0;
    
//     if(!var)
//         return ;
//     while(env && *env && (*env)[i])
//     {
//         if(!ft_strncmp((*env)[i], var, get_equal(var)))
//         {
//             free((*env)[i]);
//             (*env)[i] = ft_strdup(var);
//             return ;
//         }
//         i++;
//     }
//     if (ft_isalpha(var[0]) || var[0] == '_')
//         *env = ft_array(*env, ft_strdup(var));
//     else
//          printf("export: not a valid identifier\n");
// }
void sort_env(char **env)
{
    int i;
    int j;

    i = 0;
    while(env && env[i])
    {
        j = i + 1;
        while(env[j])
        {
            if(strcmp(env[i], env[j]) > 0)
                swap(&env[i], &env[j]);
            j++;   
        }
        i++;
    }
}

int main(int ac, char *av[], char *env[]) 
{
    (void)ac;
    (void)(*av);
    (void)(*env);
    // int i; 
    // char **array;
    
    // i = 0;
    // array = get_env_export(env);
    // sort_env(array);
    // i = -1;
    // while(array && array[++i])
    //     ft_putendl_fd(array[i], 1);
    char *s ="_3";
    // char *s ="ft_isalpha(var[1])";
    if(ft_isalpha(s[1]))
        puts("true");
    else
        puts("false");
    return 0;
}