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
void make_process(t_command *command)
{
    int fd[2];
    int pid;
    if(command->next)
    {
        if(pipe(fd) == -1)
            perror("Error creating pipe");
    }
    pid = fork();
    if(pid == -1)
        perror("Error forking");
    if(pid == 0)
    {
        if(command->input != 0)
        {
            dup2(command->input, 0);
            close(command->input);
        }
        if(command->next && command->output == 1)
        {
            dup2(fd[1], 1);
            close(fd[1]);
        }
        else if(command->output != 1)
        {
            dup2(command->output, 1);
            close(command->output);
        }
        execve(command->cmd[0], command->cmd, NULL);
        perror("Error execve");
    }
    else
    {
        close(fd[1]);
        command = command->next;
        if(command)
        command->input = fd[0];
    }
}

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
    // ft_lstadd_back1(&nodes, ft_lstnew1("<", "rd_in"));
    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    // ft_lstadd_back1(&nodes, ft_lstnew1("Makefile", "quote"));
    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("l", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("s", "quote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-l", "quote"));
    ft_lstadd_back1(&nodes, ft_lstnew1("a", "quote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    // ft_lstadd_back1(&nodes, ft_lstnew1("grep", "word"));
    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    // ft_lstadd_back1(&nodes, ft_lstnew1("S", "quote"));
    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));

    // ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("wc", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-l", "quote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    // ft_lstadd_back1(&nodes, ft_lstnew1(">", "rd_out"));
    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    // ft_lstadd_back1(&nodes, ft_lstnew1("fd_out", "quote"));

    // ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
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

// void set_newlist(t_node *node) 
// {
//     t_command *cmd = NULL;
//     char *s = NULL;
//     char **array = NULL;
//     int fd_out = 1;
//     int fd_in = 0;
//     int flag;
//     while (node) 
//     {
//         if (!ft_strncmp(node->type, "space", 5))
//         {
//             array = ft_array(array, s);
//             s = NULL;
//             node = node->next;
//         }
        
//         if (!ft_strncmp(node->type, "pipe", 4))
//         {
//             if (array)
//             {
//                 ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd_in, fd_out));
//                 array = NULL;
//                 fd_out = 1;
//                 fd_in = 0;
//             }
//             node = node->next;
//         }

//         if (!ft_strncmp(node->type, "append", 6) || !ft_strncmp(node->type, "red_out", 7))
//         {
//             flag = 0;
//             if(!ft_strncmp(node->type, "append", 6))
//                 flag = 1;
//             node = node->next;
//             while(!ft_strncmp(node->type, "space", 5))
//                 node = node->next;
//             if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "quote", 5))
//             {
//                 if(flag)
//                     fd_out = open(node->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
//                 else
//                     fd_out = open(node->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//                 node = node->next;
//             }
//             else
//                 perror("");
//         }
        
//         if(!ft_strncmp(node->type, "here_doc", 8) || !ft_strncmp(node->type, "rd_in", 5)) //< <<
//         {
//             flag = 0;
//             if(!ft_strncmp(node->type, "rd_in", 5))
//                 flag = 1;
//             node = node->next;
//             while(!ft_strncmp(node->type, "space", 5))
//                 node = node->next;
//             if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "quote", 5))
//             {
//                 if(flag)
//                     fd_in = open(node->value, O_RDONLY, 0644);
//                 else
//                     fd_in = ft_herdoc(node->value);
//                 node = node->next;
//             }
//             else
//                 perror("");
//         }

//         if( !ft_strncmp(node->type, "pipe", 4) || !ft_strncmp(node->type, "space", 5))
//             continue ;
//         s = ft_strjoin(s, node->value);
//         node = node->next;
//     }
//     printf("%s\n", s);
//     if(s)
//     {
//         array = ft_array(array, s);
//         ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array,fd_in,fd_out));
//     }
//     // printf("-------------commands------------\n");
//     // display_cmd(cmd);
//     // printf("-------------fin commands-------------\n");
//     // t_command *tmp = cmd;
//     // while(tmp)
//     // {
//     //     tmp->cmd = ft_pathname(getenv("PATH"), tmp->cmd);
//     //     tmp = tmp->next;
//     // }
//     // while(cmd)
//     // {
//     //     make_process(cmd);
//     //     cmd = cmd->next;
//     // }
//     // //
//     // wait(NULL);
//     // wait(NULL);
    
// }


char	*ft_join_free(char *s, const char *buf)
{
	char	*r;

	r = ft_strjoin(s, buf);
	free(s);
	return (r);
}

char	**ft_pathname(char *p, char **cmdargs)
{
	int		i;
	char	*cmd;
    char    **paths;

    paths = ft_split(p, ':');
    if(!paths)
        return ( NULL);
	i = -1;
    if(cmdargs[0][0] == '/')
        return (cmdargs);
	while (paths[++i])
	{
		cmd = ft_join_free(paths[i], "/");
		cmd = ft_join_free(cmd, cmdargs[0]);
		if (access(cmd, F_OK | X_OK) == 0)
			break ;
	}
    cmdargs[0] = cmd;
    // free(cmd);
	return (cmdargs);
}

void handle_space(t_node **node, char ***array, char **s) 
{
    if (!ft_strncmp((*node)->type, "space", 5)) 
    {
        *array = ft_array(*array, *s);
        // int i = -1;
        // while(aray[++i])
            // printf("%s\n", )
        *s = NULL;
        *node = (*node)->next;
    }
}

void handle_pipe(t_node **node, t_command **cmd, char ***array, int *fd_in, int *fd_out) 
{
    if (!ft_strncmp((*node)->type, "pipe", 4)) 
    {
        if (*array) 
        {
            ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(*array, *fd_in, *fd_out));
            *array = NULL;
            *fd_out = 1;
            *fd_in = 0;
        }
        *node = (*node)->next;
    }
}

void handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
    if (!ft_strncmp((*node)->type, "append", 6) || !ft_strncmp((*node)->type, "rd_out", 6)) 
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
    // if (!ft_strncmp((*node)->type, "here_doc", 8) || !ft_strncmp((*node)->type, "rd_in", 5)) 
    // {
    //     flag = 0;
    //     if (!ft_strncmp((*node)->type, "rd_in", 5))
    //         flag = 1;
    //     *node = (*node)->next;
    //     while (!ft_strncmp((*node)->type, "space", 5))
    //         *node = (*node)->next;
    //     if (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5)) 
    //     {
    //         if (flag)
    //             *fd_in = open((*node)->value, O_RDONLY, 0644);
    //         else
    //             *fd_in = ft_herdoc((*node)->value);
    //         *node = (*node)->next;
    //     }
    //     else
    //         perror("");
    // }
    // puts("here");
}

void execute_commands(t_command *cmd) 
{
    t_command *tmp;
    char *path;

    tmp= cmd;
    path = getenv("PATH");
    while(tmp) 
    {
        tmp -> cmd = ft_pathname(path, tmp->cmd);
        tmp = tmp->next;
    }
    while(cmd) 
    {
        make_process(cmd);
        cmd = cmd->next;
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
}

void set_newlist(t_node **node)
{
    t_command *cmd = NULL;
    char *s = NULL;
    char **array = NULL;
    int fd_out = 1;
    int fd_in = 0;
    int flag = 0;

    while (*node) 
    {
        handle_space(node, &array, &s);
        handle_pipe(node, &cmd, &array, &fd_in, &fd_out);
        handle_append_or_red_out(node, &fd_out, flag);
        handle_here_doc_or_rd_in(node, &fd_in, flag);
        if(!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5))
            continue ;
        s = ft_strjoin(s, (*node)->value);
        *node = (*node)->next;
    }
    if (s) 
    {
        array = ft_array(array, s);
        ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd_in, fd_out));
    }
    printf("-------------commands------------\n");
        display_cmd(cmd);
    printf("-------------fin commands-------------\n");
    execute_commands(cmd);
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
        set_newlist(&tmp);
        free(s);
    }
    return (0);
}
