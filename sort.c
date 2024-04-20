/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:15:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:31 by aben-cha         ###   ########.fr       */
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

int check_var(char *var)
{
    int i= 0;
    if(!var)
        return (0);
    if (var[0] == '_')
        i++;
    if(!ft_isalnum(var[i]))
        return (0);
    while(var[i])
    {
        if(var[i] == '=' || var[i] == '_')
            i++;
        else if(!ft_isalnum(var[i]))
            return (0);
        i++;
    }
    return (1);
}
int	is_valid_key(char *command)
{
	int	i;

	i = 0;
	if (!ft_isalpha(command[i]) && command[i] != '_')
		return (0);
	while (command[i])
	{
		if (!ft_isalnum(command[i])
			&& command[i] != '_' && command[i] != '='
			&& command[i] != '$')
			return (0);
		i++;
	}
	return (1);
}
//aben+=chafai


// export hello           valid
//export HELLO=123        valid
// export A-              not valid
//export A_123            valid 
// export HELLO="123 A-"  valid
// export ben chafai  valid => each word in line
// export =   ==> error
// export 123   ==> error

int get_equal(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '=')
            return (i);
        i++;
    }
    return (0);
}

int check_error(char *var)
{
    int i = 0;
    int j;
    int size;
    
    if(var[i] == '_')
        i++;
    j = i;
    if(!ft_isalpha(var[i]))
        return (0);
    size = get_equal(var);
    while(var[i] && (size == 0))
    {
        if(var[i]!='_')
        if (!ft_isalnum(var[i]))
            return (0);
        i++;
    }
    i += j;
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
    printf("%s\n", var);
    return (1);
}

char *get_s(char *var)
{
    int i = 0;
    return (var + get_equal(var) + 1);
}
int get_best_size(char *var)
{
    int j = 0;
    int size = get_equal(var);
    
    if(size == 0) //export only 
        j = ft_strlen(var);
    else // env && export
    {
        if(!check_char(var, '+'))
            j = size;
        else
            j = size - 1;
    }
    return (j);
}
int main(int ac, char *av[]) 
{
    (void)(ac);
    int i = 0;
    // char *var = "export=hatim";
    // char *s =NULL;
    // char *array[3] = {"aben=ay||", "export=", "unset"};
    // while(i < 3)
    // {
    //     if(!ft_strncmp(array[i], var, get_equal(var)))
    //     {
    //         char *s = ft_strjoin(array[i], var + get_equal(var) + 1);
    //         printf("(%s)\n",s);    
            
    //     }
    //     i++;
    // }
    // printf("%d\n",check_error(av[1]));    
    // printf("(%s)\n",get_s(av[1])); 
    if(!get_best_size(av[1]))
        return (0);   
    printf("%d\n",hhhh(av[1]));    
    return 0;
}