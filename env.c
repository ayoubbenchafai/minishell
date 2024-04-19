/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/19 16:57:56 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env(char **env)
{
    int i = 0;
    char **array;

    while(env[i])
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

void swap(char **a, char **b)
{   
    char *c;
    c = *a;
    *a = *b;
    *b = c;
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
            if(strcmp(env[i], env[j]) > 0) // ft_strcmp
                swap(&env[i], &env[j]);
            j++;   
        }
        i++;
    }
}

void	export_print(char **export_env)
{
    // if(!export_env || !*export_env)
        // return ; 
    int i;
    
	sort_env(export_env);
	while (export_env && *export_env)
	{
        i = 0;
		ft_putstr_fd("declare -x ", 1);
            
        while((*export_env)[i])
        {
            if((*export_env)[i] != '+')
            {
                ft_putchar_fd((*export_env)[i], 1);
                if((*export_env)[i] == '=')
                    ft_putchar_fd('"', 1);
            }
            i++;
        }
        if(check_char(*export_env, '+') && !get_equal(*export_env))
        {
            ft_putchar_fd('=', 1);
            ft_putchar_fd('"', 1);
        }
        if(get_equal(*export_env))
            ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
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
    // printf("%s\n", var);
    return (1);
}

void export_env(char *var, char ***ex_env)
{
    int i;
    size_t size;
    
    i = 0;
    size = (size_t)get_equal(var);
    if (size == 0)
        size = ft_strlen(var);
    // if(!get_equal(var))
    // {
    //     *ex_env = ft_array(*ex_env, ft_strdup(var));
    //         return ;
    // }
    while(ex_env && *ex_env && (*ex_env)[i])
    {
        
        if (!ft_strncmp((*ex_env)[i], var, size))
        {
            free((*ex_env)[i]);
            (*ex_env)[i] = ft_strdup(var);
            return ;
        }
        i++;
    }
    *ex_env = ft_array(*ex_env, ft_strdup(var));
}

// void exec_export(char *var, char ***env, char ***ex_env)
// {
//     int i;
//     int j;
    
//     i = 0;
//     j = 0;   
//     if(!var)
//     {
//         export_print(*ex_env);
//         return ;
//     }
//     if(!check_error(var)) // ghadi nbdelha b function jdida li 9adit 
//     {
//         printf("export: not a valid identifier\n");
//         return ;
//     }
//     if (ex_env && *ex_env && !get_equal(var))
//     {
//         // not equal   => strlen
//         // equal exist => get_equal
//        export_env(var, ex_env); 
//        return ;
       
//     }
//     while(env && *env && (*env)[i])
//     {
        
//         if (!ft_strncmp((*env)[i], var, get_equal(var)))
//         {
//             if(check_char(var, '+'))
//             {
//                 char *s = ft_strjoin(var ,var + get_equal(var) + 1);
//                 printf("%s\n", s);
//             }
//             else
//                 free((*env)[i]);
//             (*env)[i] = ft_strdup(var);
//             return ;
//         }
//         i++;
//     }
//     export_env(var, ex_env);
//     // while(ex_env && *ex_env && (*ex_env)[j])
//     // {
//     //     if (check_error(var) && !ft_strncmp((*ex_env)[j], var, ft_strlen(var)))
//     //     {
//     //         free((*ex_env)[j]);
//     //         (*ex_env)[j] = ft_strdup(var);
//     //         return ;
//     //     }
//     //     j++;
//     // }
//     if (check_error(var))
//     {
//         *env = ft_array(*env, ft_strdup(var));
//         *ex_env = ft_array(*ex_env, ft_strdup(var));
//     }
//     else
//         printf("export: not a valid identifier\n");
// }

void exec_export(char *var, char ***env, char ***ex_env)
{
    int i = 0;
    int j;
    
    if(!var)
    {
        export_print(*ex_env);
        return ;
    }
    if(!check_error(var))
    {
        printf("export: not a valid identifier\n");
        return ;
    }
    //env ==> obliger = exist
    //export_env ==> pas obligatoire
    if (!get_equal(var))
    {
       export_env(var, ex_env); 
       return ;
    }
    j = get_equal(var);
    if(check_char(var, '+'))
        j--;
    while(env && *env && (*env)[i])
    {
        if (!ft_strncmp((*env)[i], var, j))
        {
            if(check_char(var, '+'))
            {
                char *s = ft_strjoin((*env)[i] ,var + get_equal(var) + 1);
                (*env)[i] = ft_strdup(s);
            }
            else
            {
                free((*env)[i]);
                (*env)[i] = ft_strdup(var);
            }
            return ;
        }
        i++;
    }
    *env = ft_array(*env, var);
    *ex_env = ft_array(*ex_env, var);
}

void exec_unset(char *s, char ***env)
{
    int i = 0;
    int len = 0;
    if(!s)
        return ;
    while(env && *env && (*env)[i])
    {
        if(ft_strncmp((*env)[i], s, ft_strlen(s)))
            len++;
        i++;
    }
    char **unset_array = (char **)malloc((sizeof(char *) * (len+1)));
    if(!unset_array)
        return ;
    i = 0;
    int j = 0;
    while(env && *env && (*env)[i])
    {
        if(ft_strncmp((*env)[i], s, ft_strlen(s)))
            unset_array[j++] = ft_strdup((*env)[i]);
        i++;
    }
    unset_array[j] = NULL;
    *env = unset_array;
}

int exec_env(char **env)
{
    int i;

    i = 0;
    while(env && env[i])
    {
        ft_putstr_fd(env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return 0;
}

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
int expand(char *var, char **env)
{
    int i;

    i = 0;
    if (!check_char(var, '$'))
        return (0);
    char *trim = ft_strnstr(var, "$",ft_strlen(var));
    while (env && env[i])
    {
        if (!ft_strncmp(env[i], trim + 1, get_equal(env[i])))
        {
            ft_putstr_fd(env[i] + get_equal(env[i]) + 1, 1);
            ft_putstr_fd("\n", 1);
            return (1);
        }
        i++;
    }
    return 0;
}
