/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:16:02 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/07 23:16:18 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void exec_unset(char *s, char ***env, t_node **addresses)
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
    char **unset_array = ft_malloc(sizeof(char *) * (len + 1), addresses);
    if(!unset_array)
        return ;
    i = 0;
    int j = 0;
    while(env && *env && (*env)[i])
    {
        // if(ft_strcmp((*env)[i], s))
        if(ft_strncmp((*env)[i], s, get_equal((*env)[i]))) // ila kan (=) f string
            unset_array[j++] = ft_strdup((*env)[i], addresses);
        i++;
    }
    unset_array[j] = NULL;
    *env = unset_array;
    exit_status(0);
}