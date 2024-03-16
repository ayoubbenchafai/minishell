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

void display(t_node *node)
{
    int i = 1;
    if(!node)
        return ;
    while(node)
    {
        printf("node %d => value : %s, type : %s\n", i++,node->value, node->type);
        node = node->next;
    }
}


t_node *fill_list_commands(t_node *node, char *array, int start, int end)
{
    t_node *new;
    char *tmp;

    tmp = ft_substr(array, start, end);
    new = ft_lstnew1(tmp, "word");
    if (!new)
        return (free(array), free(array), free(tmp), NULL);
    ft_lstadd_back1(&node, new);
    return (node);
    // return (0);
}

t_node *get_node(t_node *nodes)
{
    ft_lstadd_back1(&nodes, ft_lstnew1("l", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-l", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1("a", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("grep", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));


    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    
    // probleme in this 
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("echo", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-n", "squote"));

    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("$PATH", "expand"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1(">>", "append"));
    ft_lstadd_back1(&nodes, ft_lstnew1("file", "word"));


    return nodes;
}

char *set_line(t_node *node)
{
    char *s;

    s = NULL;
    while(node)
    {
        s = ft_strjoin(s, node->value);
        node = node -> next;
    }
    return (s);
}
int get_char(char c)
{
    if(c == '<' || c == '>')
        return (1);
    return (0);
}

int check_redirections(char *s)
{
    // char *ptr = "|><$";
    char *ptr = "><";

    while(*s)
    {
        if(ft_check(ptr, *s))
            return (1);
        s++;
    }
    return (0);
}

void set_newlist(t_node *node)
{
   t_node *head = NULL;
    t_node *new;
    char *s = NULL;
    while(node)
    {
        if(ft_strncmp(node->value, "|", 1))
        // if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "squote", 6)
        //   || !ft_strncmp(node->type, "dquote", 6) || !ft_strncmp(node->type, "space", 5) ||
        //    !ft_strncmp(node->type, "expand", 6))
        {
            s = ft_strjoin(s, node->value);
            printf("s : %s\n", s);
        }
        else if (!ft_strncmp(node->value, "|", 1))
        {
                printf("---> s : %s\n", s);
                
                new = ft_lstnew1(s, "test"); 
                ft_lstadd_back1(&head, new);
                s = NULL;
        }
        node = node ->next;        
    }
    ft_lstadd_back1(&head, ft_lstnew1(s, "cmd"));
    
    printf("-------------commands------------\n");
    display(head);
    printf("-------------fin commands-------------\n");
}

int main()
{
    char *s;
    t_node *node;
    t_node *tmp;
    
    node = NULL;
    char *string;
    while(1)
    {
        s  = readline("minishell $ ");
        if(!s)
            return (1);
        if(s)
            add_history(s);
        if(!ft_strncmp(s,"exit", 4))
            return (free(s), 0);
        tmp = get_node(node);
        if(!tmp)
            return (free(s), 1);
        string = set_line(tmp);
        printf("%s\n", string);
        set_newlist(tmp);
        // display(tmp);
        free(s);
    }
    return (0);
}