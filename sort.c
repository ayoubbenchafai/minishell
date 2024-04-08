/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:15:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/08 03:19:45 by aben-cha         ###   ########.fr       */
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
char *join_export(char *var)
{
    int i = 0;
    char *s;
    while(var[i])
    {
        if(var[i] == '+')
            s = ft_strdup(var + i);
        i++;
    }
    // printf("%s\n", s);
    return (s);
}

// export hello           valid
//export HELLO=123        valid
// export A-              not valid
//export A_123            valid 
// export HELLO="123 A-"  valid
// export ben chafai  valid => each word in line
// export =   ==> error
// export 123   ==> error
int main(int ac, char *av[]) 
{
    // (void)(ac);
    if(!av[1])
        return (1);
        printf("%s\n", join_export(av[1]));
        printf("%s\n", join_export(av[1]));
    return 0;
}