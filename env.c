/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/18 15:19:33 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_env(char **env)
{
    int i = 0;
    char **array;
    while(env[i])
        i++;
    array = malloc((sizeof(char *) * (i + 1)));
    if (!array)
        return (NULL);
    i = 0;
    while(env && env[i])
    {
        array[i] = malloc((sizeof(char) * (ft_strlen(env[i]) + 1)));
        if (!array[i])
            return (NULL);
        ft_strlcpy(array[i], env[i], ft_strlen(env[i]) + 1);
        i++;
    }
    array[i] = NULL;
    return (array);
}

int get_equal(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '=')
            return i;
        i++;
    }
    return 0;
}
int get_dollar(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '$')
            return i;
        i++;
    }
    return 0;
}
int check_char(char *s,char c)
{
    while(s && *s)
    {
        if(*s == c)
            return 1;
        s++;
    }
    return (0);
}

void    expand(t_node *node, t_env *env, t_node **addresses, char *response)
{
    char *var;
    int i;
    int x;

    x = 0;
    i = 0;
    if (!node || !ft_strcmp(node->type, "s_quote"))
        return ;
    while(node->value && ((char *)node->value)[i])
    {
        while(((char *)node->value)[i] != '\0')
        {
            if (((char *)node->value)[i] == '$' && ft_isalnum(((char *)node->value)[i + 1]))         
                break ;
            i++;
        }
        response = ft_strjoin(response, ft_substr(node->value, x, i - x , addresses), addresses);
        if (((char *)node->value)[i] != '\0')
            i++;
        x = i;
        while(((char *)node->value)[i] != '\0' && ft_isalnum(((char *)node->value)[i]))
            i++;
        var = ft_substr(node->value, x, i - x, addresses);
        response = ft_strjoin(response, get_environment(env->env, var, addresses), addresses);
        x = i;
    }
    node->value = response;
    return ;
}
