/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:15:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/29 22:29:29 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
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

int exit_status(int exit_status)
{
    static int n = 0;
    if(exit_status != -1)
        n = exit_status;
    return (n);
}
typedef struct s_heredoc
{
    int fd_write;
    int fd_read;
}   t_heredoc;

// static void  ft_read_input(char *s, t_heredoc *heredoc)
// {
//     char *line;
//     char *tmp;
//     while(1)
//     {
//         // if(exit_status(-1) == 1)
//         //     break ;  
//         line = readline("heredoc> ");
//         if(!line)
//             break ;
//         if(!ft_strncmp(line, s, ft_strlen(s)) && ft_strlen(line) == ft_strlen(s))
//         {
//             free(line);
//             break;
//         }
//         tmp = ft_strjoin(line, "\n");
//         write(heredoc->fd_write, tmp, ft_strlen(tmp));
//         free(tmp);
//         free(line);
//     }
//     close(heredoc->fd_write);
//     close(heredoc->fd_read);
    
// }
// int ft_herdoc(char *s)
// {
//     int         pid;
//     t_heredoc   heredoc;
//     heredoc.fd_write = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
//     heredoc.fd_read = open("here_doc", O_RDONLY, 0644);
//     if(heredoc.fd_write == -1 || heredoc.fd_read == -1 || unlink("here_doc") == -1)
//         return (-1);
//     pid = fork();
//     if(pid == -1)
//         return (-1);
//     if(pid == 0)
//     {
//         ft_read_input(s, &heredoc);
//         exit(0);
//     }
//         wait(NULL);
//     close(heredoc.fd_write);
//     return (heredoc.fd_read);
// }

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
        printf("exit ,  %d\n", ft_atoi(cmd[1]) % 256);
        //exit_status(ft_atoi(cmd[1]));
        exit(ft_atoi(cmd[1]));//khsha tbdel exit status
    }
}
int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long  long		result;
	long  long		prev;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
        prev = result;
		result = (result * 10) + str[i] - '0';
        // printf("prev : %lld, result: %lld\n", prev, result);
        if(prev != result / 10)
        {
            ft_putendl_fd("exit", 2);
            ft_putendl_fd("minishell: numeric argument required", 2);
            exit_status(255);
            exit(-1);
        }
		i++;
	}
	return (sign * result);
}
void get_exit_value(char *av)
{
    //255 = > 255
    //256 => 0
    //257 => 1
    // 2147483648 => 0
    //9223372036854775807 => 255
    //9223372036854775807> => 255 error numeric argument required
    int res = ft_atoi(av);
    printf("res: %d\n", res);
    if(res < 0)
        res = 256 + res;
    else
        res = res % 256;
    printf("exit: %d\n", res);
    exit(res);
}
int main(int ac, char *av[]) 
{
    // int i = 0;
    // while(++i < ac)
    //     get_exit_value(av[i]);
    //     // exec_exit(av + i);

    printf("exit: %d\n", ft_atoi(av[1]));
    return 0;
}
