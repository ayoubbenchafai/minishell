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
void display_cmd(t_command *cmd)
{
    int i = 1;
    if(!cmd)
        return ;
    while(cmd)
    {
        printf("cmd %d => cmd : %s, intput : %d, output : %d\n", i++, cmd->cmd, cmd->input, cmd->output);
        cmd = cmd->next;
    }
}

char *set_type(char *s)
{
    char *tmp;
    
    tmp = NULL;
    if(!ft_strncmp(s, "<<", 2))
        tmp =  "herdoc";
    else if(!ft_strncmp(s, ">>", 2))
        tmp = "red_out_append";
    else if(!ft_strncmp(s, ">", 1))
        tmp = "red_out_trunc";
    else if(!ft_strncmp(s, "<", 1))
        tmp = "red_in";
    else if(!ft_strncmp(s, "|", 1))
        tmp = "pipe";
    else if(!ft_strncmp(s, "$", 1))
        tmp =  "expand";
    // else
    //     tmp = "word";
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

    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));

    ft_lstadd_back1(&nodes, ft_lstnew1("grep", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));

    return nodes;
}
int check_redirections(char *s)
{
    char *ptr = "|><$";

    while(*s)
    {
        if(ft_check(ptr, *s))
            return (1);
        s++;
    }
    return (0);
}
void fill_list_of_commands(t_node *node)
{
    // t_node *ptr;
    // ls -la | grep aben-cha
    t_command *cmds = NULL;
    char *s;
    while(node)
    {
        printf("node->type : %s\n", node->type);

        if(check_redirections(node->value))
            break;        
        if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "squote", 6)
          || !ft_strncmp(node->type, "dquote", 6) || !ft_strncmp(node->type, "space", 5))
        {
            // if(!ft_strncmp(node->type, "|", 1))
            //     break; 
            s = ft_strjoin(s, node->value);
            
        }
        node = node ->next;        
    }
    printf("result : %s\n", s);
    ft_lstadd_back_cmd(&cmds, ft_lstnew_cmd(s, 0, 1));
    display_cmd(cmds);
}

int main()
{
    char *s;
    t_node *node;
    t_node *tmp;
    
    node = NULL;
    while(1)
    {
        s  = readline("minishell$ ");
        if(!s)
            return (1);
        if(s)
            add_history(s);
        if(!ft_strncmp(s,"exit", 4))
            return (free(s), 0);
        tmp = get_node(node);
        if(!tmp)
            return (free(s), 1);
        fill_list_of_commands(tmp);
        // pause();
        display(tmp);
        // node = get_node(nodes);
        free(s);
    }
    return (0);
}