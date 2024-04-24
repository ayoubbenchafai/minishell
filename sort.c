/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:15:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/24 12:51:08 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

int get_equal(char *s, char c)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == c)
            return (i);
        i++;
    }
    return (0);
}

// int check_error(char *var)
// {
//     int i = 0;
//     int j;
//     int size;
    
//     if(var[i] == '_')
//         i++;
//     j = i;
//     if(!ft_isalpha(var[i]))
//         return (0);
//     size = get_equal(var);
//     while(var[i] && (size == 0))
//     {
//         if(var[i]!='_')
//         if (!ft_isalnum(var[i]))
//             return (0);
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
//             else 
//                 return (0);
//              }
//         if (!ft_isalnum(var[i]))
//             return (0);
//         }
//         i++;
//     }
//     printf("%s\n", var);
//     return (1);
// }

char *get_s(char *var)
{
    int i = 0;
    return (var + get_equal(var, '=') + 1);
}
// int get_best_size(char *var)
// {
//     int j = 0;
//     int size = get_equal(var);
    
//     if(size == 0) //export only 
//         j = ft_strlen(var);
//     else // env && export
//     {
//         // if(!check_char(var, '+'))
//         //     j = size;
//         // else
//         //     j = size;
        
//         if(var[size - 1] == '+' && var[size] == '=')
//             j = size - 1;
//         else if(var[size] == '=')
//             j = size + 1;
//         else
//             j = size;
//     }
//     return (j);
// }

void	export_print(char **export_env)
{
    // if(!export_env || !*export_env)
    //     return ; 
    int i;
    
	// sort_env(export_env);
	while (export_env && *export_env)
	{
        i = 0;
		ft_putstr_fd("declare -x ", 1);
        while((*export_env)[i])
        {
            if((*export_env)[i] != '+')
            {
                if(!(*export_env)[i + 1])
                    ft_putchar_fd((*export_env)[i], 1);
                if((*export_env)[i] == '=')
                    ft_putchar_fd('"', 1);
            }
            i++;
        }
        if(check_char(*export_env, '+') && !get_equal(*export_env, '='))
        {
            ft_putchar_fd('=', 1);
            ft_putchar_fd('"', 1);
        }
        if(get_equal(*export_env, '='))
            ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
}

int get_len_char(char *s, char c)
{
    int i = 0;
    int len= 0;
    while(s && s[i])
    {
        if(s[i] == c)
            return (i);
        i++;
    }
    return (len);
}
// int get_best_size(char *var)
// {
//     int j = 0;
//     int size = get_equal(var);
    
//     if (size == 0) //export only 
//         j = ft_strlen(var);
//     else // env && export
//     {
//         if(!check_char(var, '+'))
//             j = size;
//         else
//             j = size - 1;
//     }
//     return (j);
// }
char	*get_environment(char **envp, char *var)
{
	int		i;
	char	*response;

	response = NULL;
	i = 0;
	while (envp && envp[i])
	{
		response = ft_strnstr(envp[i], var, ft_strlen(var));
		if (response)
            return response + ft_strlen(var);
		i++;
	}
	return (NULL);
}


int set_expand(char *var)
{
    int i = 0;
    char *s;
    while(var && var[i])
    {
        if(var[i]=='$')
            i++;
        else 
            return(i);
        i++;
    }
    return (i);
}
//$$$$USER$$$$ ==> should print $$$username$$$$
//$$$aben-cha$$$
void exec_exit(char **cmd)
{
    if(!cmd[1])
        exit(0);
    else if (cmd && cmd[1] && cmd[2])
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        // exit_status(1);
    }
    else
    {
        int i = 0;
        while(cmd && cmd[1][i])
        {
            if(!ft_isdigit(cmd[1][i]))
            {
                ft_putstr_fd("exit\n", 2);
                ft_putstr_fd("minishell: exit: ", 2);
                ft_putstr_fd(cmd[1], 2);
                ft_putstr_fd(": numeric argument required\n", 2);
                //exit_status(255);
                exit(255);
            }
            i++;
        }
    }
    if(cmd  && cmd[1])
    {
        printf("exit ,  %d\n", ft_atoi(cmd[1]));
        //exit_status(ft_atoi(cmd[1]));
        exit(ft_atoi(cmd[1]));//khsha tbdel exit status
    }
}

void get_exit_value(char *av)
{
    //255 = > 255
    //256 => 0
    //257 => 1
    // 2147483648 => 0
    //9223372036854775807 => 255
    //9223372036854775807> => 255 error numeric argument required
    unsigned long  res = ft_atoi(av);
    res = res % 256;
    printf("exit: %d\n", (int)res);
    // exit(res);
}
int main(int ac, char *av[]) 
{
    int i = 0;
    while(++i < ac)
        // exec_exit(av + i);
        get_exit_value(av[i]);
    return 0;
}
