/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:33:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/20 12:56:39 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void env_export_all_cases(char *var, char ***env, int size)
{
    int i;   
    
    size = get_best_size(var);    
    while(env && *env && (*env)[i])
    {
        if (!ft_strncmp((*env)[i], var, size))
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

void exec_export(char *var, char ***env, char ***ex_env)
{
    int i = 0;
    int j;
    int size;
    
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
    size = get_best_size(var);
    if (!get_equal(var))
    {
    //    export_env(var, ex_env); 
       env_export_all_cases(var, ex_env, size);
       return ;
    }
    env_export_all_cases(var, ex_env, size); 
    env_export_all_cases(var, env, size); 
    //env
}
