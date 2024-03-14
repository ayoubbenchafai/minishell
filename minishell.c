/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:20:49 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/14 00:38:10 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void display(t_node *node)
{
    if(!node)
        return ;
    while(node)
    {
        printf("value : %s, type : %s\n", node->value, node->type);
        node = node->next;
    }
}

char *set_type(char *s)
{
    char *tmp;
    
    tmp = NULL;
    if(!ft_strncmp(s, "<<", 2))
        tmp =  "herdoc";
    else if(!ft_strncmp(s, ">>", 2))
        tmp = "output_redirection_append";
    else if(s[0] == '>')
        tmp = "output_redirection";
    else if(s[0] == '<')
        tmp = "input_redirection";
    else if(s[0] == '|' && s[1] == '\0')
        tmp = "pipe";
    else if(s[0] == '$' && s[1])
        tmp =  "expand";
    else
        tmp = "word";
    return (tmp);
}

int fill_list(t_node *node, char *s)
{
    int i;
    t_node *new;
    char **array;
    
    i = 0;
    array = ft_split(s, ' ');
    if(!array)
        return (free(s), 1);
    while(array[i])
    {
        new = ft_lstnew1(array[i], set_type(array[i]));
        if(!new)
            return (free(s),free_array(array), 1);
        ft_lstadd_back1(&node, new);
        i++;
    }
    display(node);
    return (0);
}



// int check_command(char *s, char **array ) split by '|'
int check_command(char *s, t_node *node)
{
    char **array; 
    t_node *new;
    char *tmp;
    char *tmp2;
    if (!ft_check(s, '|'))
        return (1);
    array = ft_split(s, '|');
    if (!array)
        return (1);
    int i = 0;
    int j;
    int k = 0;
    while(array[i])
    {
        // < Makefile grep cc |  ls -la
        // 0123456789
        if(array[i][0] == '<')
        {
            j = 1;
            while(array[i][j] == ' ')
                j++;
            k = j;
            while(array[i][k] != ' ')
                k++;
            tmp = ft_substr(array[i], 0, k);
            new = ft_lstnew1(tmp, "word");
            if (!new)
                return (free(s), free_array(array), free(tmp), 1);
            ft_lstadd_back1(&node, new);
            printf("\ntmp : %s\n", tmp);
            while(array[i][k] == ' ')
                k++;
            tmp2 = ft_substr(array[i], k, ft_strlen(array[i]));
            new = ft_lstnew1(tmp2, "word");
            if (!new)
                return (free(s), free_array(array), free(tmp2), 1);
            ft_lstadd_back1(&node, new);
            printf("tmp2 : %s\n", tmp2);
            // printf("%c", array[i][k]);
            // printf("\ntest k : %d\n", k - start);
        }
        i++;
    }
    printf("---------node :-------\n");
    display(node);
    printf("-----------------------\n");
    free_array(array);
    return (0);
}

// void fill_list_commands(t_node *node, char *array, int start, int end)
// {
//     char *tmp;

//     tmp = ft_substr(array[i], start, end);
//     new = ft_lstnew1(tmp, "word");
//     if (!new)
//         return (free(s), free_array(array), free(tmp), 1);
//     ft_lstadd_back1(&node, new);

// }

int main()
{
    char *s;
    t_node *node;
    
    node = NULL;
    while(1)
    {
        s  = readline("minishell$ ");
        if(!s)
            return (1);
        // if(!ft_strncmp(s,"exit", 4))
        //     return (free(s), 0);
        if(check_command(s, node))
            return (free(s), 1);
        if(fill_list(node, s))
            return (1);
        free(s);
    }
    return (0);
}