/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:12:58 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/07 23:15:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sort_env(char **env)
{
    int i;
    int j;

    i = 0;
    while(env && env[i])
    {
        j = i + 1;
        while (env[j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
                swap(&env[i], &env[j]);
            j++;   
        }
        i++;
    }
}

void	export_print(char **export_env)
{
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
                ft_putchar_fd('"', 1);
            i++;
        }
        if(check_char(*export_env, '+') && !get_equal(*export_env))
            ft_putstr_fd("=\"", 1);
        if(get_equal(*export_env))
            ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
    exit_status(0);
}

void export_join(int flag, char *var, char **env, t_node **addresses)
{
    char *s;

    if (!flag)
    s = ft_strjoin(*env ,var + get_equal(var) + 1, addresses);
    else
        s = ft_strjoin(*env ,var + get_equal(var), addresses);
    *env = ft_strdup(s, addresses);
}

void env_export_all_cases(char *var, char ***env, int size, t_node **addresses)
{
    int i;   
    int len;
    int flag;
    
    i = 0;
    flag = 0;
    len = get_equal(var);
    while(env && *env && (*env)[i])
    {
        if (!ft_strncmp((*env)[i], var, size) && !check_char(var, '='))
            return ;
        else if (!ft_strncmp((*env)[i], var, size) && check_char(var, '='))
        {
            if(!check_char((*env)[i], '='))
                flag = 1;
            if (var[len - 1] == '+' && var[len] == '=')
                export_join(flag, var, &(*env)[i], addresses);
            else
                (*env)[i] = ft_strdup(var, addresses);
            return ;
        }
        i++;
    }
    *env = ft_array(*env, var, addresses);
}

void exec_export(char **vars, char ***env, char ***ex_env, t_node **addresses)
{
    int i;
    int size;
    
    i = 1;
    if(!vars || !*vars || !vars[1])
    {
        export_print(*ex_env);
        return ;
    }
    while(vars && vars[i])
    {
        size = get_best_size(vars[i]);
        if (!check_error(vars[i]))
        {
            printf("export: `%s':not a valid identifier\n", vars[i++]); 
            exit_status(1);
        }
        if (!get_equal(vars[i]))
        {
            env_export_all_cases(vars[i++], ex_env, size, addresses);
            continue ;
        }
        env_export_all_cases(vars[i], ex_env, size, addresses);
        env_export_all_cases(vars[i++], env, size, addresses);
    }
}