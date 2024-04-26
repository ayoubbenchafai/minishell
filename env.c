/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/26 12:44:37 by aben-cha         ###   ########.fr       */
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

// 

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
            ft_putchar_fd(env[i][j], 1);
            j++;
        }
        ft_putstr_fd("\n", 1);
        i++;
    }
    return 0;
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
            if ((*export_env)[i]== '+' && (*export_env)[i + 1] == '=')
                i++;
            ft_putchar_fd((*export_env)[i], 1);
            if ((*export_env)[i] == '=' && (*export_env)[i - 1] != '=')
            {
                ft_putchar_fd('"', 1);
                // if(check_char(*export_env, '"'))
                //     ft_putchar_fd('\\', 1);
            }
            i++;
        }
        if(check_char(*export_env, '+') && !get_equal(*export_env))
        {
            ft_putchar_fd('=', 1);
            ft_putchar_fd('"', 1);
        }
        if(get_equal(*export_env))
        {
            // if(check_char(*export_env, '"'))
            //     ft_putchar_fd('\\', 1);
            ft_putchar_fd('"', 1);
        }
		ft_putstr_fd("\n", 1);
		export_env++;
	}
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

int get_best_size(char *var)
{
    int j = 0;
    int size = get_equal(var);
    
    if (size == 0) //export only 
        j = ft_strlen(var);
    else // env && export
    {
        if(var[size - 1] == '+' && var[size] == '=')
            j = size - 1;
        else
            j = size;
    }
    return (j);
}

int get_len_char(char *s, char c)
{
    int i = 0;
    while(s && s[i])
    {
        if(*s != c)
            return (0);
        i++;
    }
    return (i);
}
void env_export_all_cases(char *var, char ***env, int size)
{
    int i;   
    int len;
    
    i = 0;
    len = get_equal(var);
    while(env && *env && (*env)[i])
    {
        if (!ft_strncmp((*env)[i], var, size) && !check_char(var, '='))
            return ;
        else if (!ft_strncmp((*env)[i], var, size) && check_char(var, '='))
        {
            if(var[len - 1] == '+' && var[len] == '=')
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
    exit_status(0);
}



void exec_export(char **vars, t_env *enviroment)
{
    int i;
    int size;
    
    i = 1;
    if(!vars || !vars[1])
    {
        export_print(enviroment->export);
        return ;
    }
    while(vars && vars[i])
    {
        size = get_best_size(vars[i]);
        if(!check_error(vars[i]))
        {
            printf("export: not a valid identifier\n");
            exit_status(1);
            return ;
        }
        if (!get_equal(vars[i]))
        {
            env_export_all_cases(vars[i++], &enviroment->export, size);
            continue ;
        }
        env_export_all_cases(vars[i], &enviroment->export, size);
        env_export_all_cases(vars[i], &enviroment->env, size);
        i++;
    }
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
    char **unset_array = (char **)malloc((sizeof(char *) * (len + 1)));
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
    exit_status(0);
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
    char *trim;

    i = 0;
    // trim = ft_strnstr(var, "$",ft_strlen(var));
    trim = ft_strtrim(var, "$");
    
    while (env && env[i])
    {
        if (!ft_strncmp(env[i], trim, get_equal(env[i])))
        {
            ft_putstr_fd(env[i] + get_equal(env[i]) + 1, 1);
            ft_putchar_fd('\n', 1);
            return (1);
        }
        i++;
    }
    return (0);
}
