/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:22:47 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/18 00:59:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_space(t_node **node, char **array, char **s) 
{
    if (!ft_strncmp((*node)->type, "space", 5)) 
    {
        array = ft_array(array, *s);
        *s = NULL;
        *node = (*node)->next;
    }
}

void handle_pipe(t_node **node, t_command **cmd, char **array, int *fd_in, int *fd_out) 
{
    if (!ft_strncmp((*node)->type, "pipe", 4)) 
    {
        if (array) 
        {
            ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(array, *fd_in, *fd_out));
            array = NULL;
            *fd_out = 1;
            *fd_in = 0;
        }
        *node = (*node)->next;
    }
}

void handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
    if (!ft_strncmp((*node)->type, "append", 6) || !ft_strncmp((*node)->type, "red_out", 7)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "append", 6))
            flag = 1;
        *node = (*node)->next;
        while (!ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5)) 
        {
            if (flag)
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            *node = (*node)->next;
        } 
        else
            perror("");
    }
}

void handle_here_doc_or_rd_in(t_node **node, int *fd_in, int flag) 
{
    if (!ft_strncmp((*node)->type, "here_doc", 8) || !ft_strncmp((*node)->type, "rd_in", 5)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "rd_in", 5))
            flag = 1;
        *node = (*node)->next;
        while (!ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5)) 
        {
            if (flag)
                *fd_in = open((*node)->value, O_RDONLY, 0644);
            else
                *fd_in = ft_herdoc((*node)->value);
            *node = (*node)->next;
        }
        else
            perror("");
    }
}

// void handle_other_types(t_node **node, char **s) 
// {
//     if (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5))
//         return;
//     *s = ft_strjoin(*s, (*node)->value);
//     *node = (*node)->next;
// }

void set_newlist(t_node *node)
{
    t_command *cmd = NULL;
    char *s = NULL;
    char **array = NULL;
    int fd_out = 1;
    int fd_in = 0;
    int flag;

    while (node) 
    {
        handle_space(&node, array, &s);
        handle_pipe(&node, &cmd, array, &fd_in, &fd_out);
        handle_append_or_red_out(&node, &fd_out, flag);
        handle_here_doc_or_rd_in(&node, &fd_in, flag);
        if( !ft_strncmp(node->type, "pipe", 4) || !ft_strncmp(node->type, "space", 5))
            continue ;
        s = ft_strjoin(s, node->value);
        node = node->next;
    }
    if (s) 
    {
        array = ft_array(array, s);
        ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd_in, fd_out));
    }
}

