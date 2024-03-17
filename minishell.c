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

void display_cmd(t_command *node)
{
    int i;
    while(node)
    {   
        printf("input : %d\n", node->input);
        printf("output : %d\n", node->output);
        printf("cmd : [");
        i = 0;
        while(node->cmd && node->cmd[i])
        {
            printf("%s,", node->cmd[i]);
            i++;
        }
        printf("]\n");
        printf("\n");
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
    ft_lstadd_back1(&nodes, ft_lstnew1("<", "rd_in"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("file1", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("l", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-l", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1("a", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("grep", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));


    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("echo", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-n", "squote"));

    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("$PATH", "expand"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1(">>", "append"));
    ft_lstadd_back1(&nodes, ft_lstnew1("file2", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));

    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("cat", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "sqoute"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-e", "sqoute"));
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

char **ft_array(char **array, char *s)
{
    char **new;
    int i;
    int j;

    i = 0;
    j = 0;
    if (!array)
    {
        new = (char **)malloc(sizeof(char *) * 2);
        new[0] = s;
        new[1] = NULL;
        return new;
    }
    else
    {
        while (array[i])
            i++;
        new = (char **)malloc(sizeof(char *) * (i + 2));
    }
    while (array[j])
    {
        new[j] = array[j];
        j++;
    }
    new[j] = s;
    new[j + 1] = NULL;
    free(array);
    return new;
}
int ft_herdoc(char *s)
{
    int fd[2];
    char *line;
    char *tmp;
    pipe(fd);
    dup2(fd[0], 0);
    while(1)
    {
        line = readline("heredoc>");
        if(!line)
            break;
        if(!ft_strncmp(line, s, ft_strlen(s)))
        {
            free(line);
            break;
        }
        tmp = ft_strjoin(line, "\n");
        write(fd[1], tmp, ft_strlen(tmp));
        free(tmp);
        free(line);
    }
    close(fd[1]);
    return (fd[0]);
}
void set_newlist(t_node *node) 
{
    t_command *cmd = NULL;
    char *s = NULL;
    char **array = NULL;
    int fd_out = 1;
    int fd_in = 0;
    while (node) 
    {
        if (!ft_strncmp(node->type, "space", 5))
        {
            array = ft_array(array, s);
            s = NULL;
            node = node->next;
        }
        if (!ft_strncmp(node->type, "pipe", 4))
        {
            if (array)
            {
                ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array,fd_in,fd_out));
                array = NULL;
                fd_out = 1;
                fd_in = 0;
            }
            node = node->next;
        }
        if (!ft_strncmp(node->type, "append", 6)) //> >>
        {
            node = node->next;
            while(!ft_strncmp(node->type, "space", 5))
                node = node->next;
            if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "quote", 5))
            {
                fd_out = open(node->value, O_CREAT | O_RDONLY | O_APPEND, 0644);
                node = node->next;
            }
            else
            {
                perror("");
                // exit(0);
            }
        }
        if(!ft_strncmp(node->type, "rd_in", 5) || !ft_strncmp(node->type, "here_doc", 8)) //< <<
        {
            node = node->next;
            while(!ft_strncmp(node->type, "space", 5))
                node = node->next;
            if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "quote", 5))
            {
                if(!ft_strncmp(node->type, "rd_in", 5))
                    fd_in = open(node->value, O_RDONLY, 0644);
                else
                    fd_in = ft_herdoc(node->value);
                node = node->next;
            }
            else
                perror("");
        }

        if( !ft_strncmp(node->type, "pipe", 4) || !ft_strncmp(node->type, "space", 5))
            continue ;
        s = ft_strjoin(s, node->value);
        node = node->next;
    }
    array = ft_array(array, s);
    ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array,fd_in,fd_out));
    printf("-------------commands------------\n");
    display_cmd(cmd);
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
        display(tmp);
        free(s);
    }
    return (0);
}
