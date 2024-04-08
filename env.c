/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/08 03:00:27 by aben-cha         ###   ########.fr       */
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

// void exec_export(char *var, char ***env)
// {
//     int i;
//     i = 0;
//     if(!var)
//     {
//         set_export(*env);
//     }
//         return ;
//    while(env && *env && (*env)[i])
//    {
//         if(!ft_strncmp((*env)[i], var, get_equal(var)))
//         {
//             free((*env)[i]);
//             (*env)[i] = ft_strdup(var);
//             return ;
//         }
//         i++;
//    }
//     if(ft_isalpha(var[0]) || var[0] == '_')
//         *env = ft_array(*env, ft_strdup(var));
//     else
//          printf("export: not a valid identifier\n");
// }
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
    if(!export_env || !*export_env)
        return ; 
	sort_env(export_env);
	while (*export_env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(*export_env, 1);
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

void export_env(char *var, char ***ex_env)
{
    int i;
    i = 0;
    
    if(!is_valid_key(var))
    {
        printf("export: not a valid identifier\n");
        return ;
    }
    if (ex_env && *ex_env && !ft_strncmp((*ex_env)[i], var, get_equal(var)))
    {
        free((*ex_env)[i]);
        (*ex_env)[i] = ft_strdup(var);
        return ;
    }
    *ex_env = ft_array(*ex_env, ft_strdup(var));
        return ;
}

void exec_export(char *var, char ***env, char ***ex_env)
{
    int i;
    i = 0;
    
    if(!var)
    {
        export_print(*ex_env);
        return ;
    }
    if (ex_env && *ex_env && !get_equal(var))
    {
       export_env(var, ex_env);
       return ;
    }
    while(env && *env && (*env)[i])
    {
        
        if (is_valid_key(var) && !ft_strncmp((*env)[i], var, get_equal(var)))
        {
            free((*env)[i]);
            (*env)[i] = ft_strdup(var);
            return ;
        }
        i++;
    }
    printf("[test : %s]\n", var);

    if (is_valid_key(var))
    {
        *env = ft_array(*env, ft_strdup(var));
        *ex_env = ft_array(*ex_env, ft_strdup(var));
    }
    else
        printf("export: not a valid identifier\n");
}

// void exec_export(char *var, char ***env, char ***export_env)
// {
//     int i;
//     i = 0;
    
//     if(!var)
//     {
//         // sort_env(*export_env);
//         export_print(*export_env);
//         return ;
//     }
//     while(env && *env && (*env)[i])
//     {
//         if (!get_equal(var))
//         {
//             if(!is_valid_key(var))
//             {
//                 printf("export: not a valid identifier\n");
//                 return ;
//             }
//             if (!export_env && !*export_env && !ft_strncmp((*export_env)[i], var, get_equal(var)))
//             {
//                 free((*export_env)[i]);
//                 (*export_env)[i] = ft_strdup(var);
//                 return ;
//             }
//             *export_env = ft_array(*export_env, ft_strdup(var));
//                 return ;
//         }
//         if (!ft_strncmp((*env)[i], var, get_equal(var)))
//         {
//             free((*env)[i]);
//             (*env)[i] = ft_strdup(var);
//             return ;
//         }
//         i++;
//     }
//     if (is_valid_key(var))
//     {
//         *env = ft_array(*env, ft_strdup(var));
//         *export_env = ft_array(*export_env, ft_strdup(var));
//     }
//     else
//          printf("export: not a valid identifier\n");
// }

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
