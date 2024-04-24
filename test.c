/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:58:52 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/24 15:11:48 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void display_cmd(t_command *node)
{
    int i;
    while(node)
    {   
        printf("input : %d\n", node->input);
        printf("output : %d\n", node->output);
        printf("cmd : [");
        i = 0;
        while(node && node->cmd && node->cmd[i])
        {
            printf("%s,", node->cmd[i]);
            i++;
        }
        printf("]\n");
        printf("\n");
        node = node->next;
    }
}
t_command *set_newlist(t_node **node)
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
        if(*node && (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5)))
            continue ;
        if(*node)
        {
            s = ft_strjoin(s, (*node)->value);
            (*node) = (*node)->next;
        }
    }
    array = ft_array(array, s);
    if(array)
        ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd_in, fd_out));
    if(pipe_parse_error(cmd) == 127)
        return NULL;
    printf("-------------commands------------\n");
    display_cmd(cmd);
    printf("-------------fin commands-------------\n");
    return cmd;
}

void handle_space(t_node **node, char ***array, char **s) 
{
      if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "space", 5))
    {
        *array = ft_array(*array, *s);
        *s = NULL;
        *node = (*node)->next;
    }
    else if (!ft_strncmp((*node)->type, "pipe", 4))
    {
        *array = ft_array(*array, *s);
        *s = NULL;
    }
}

void handle_pipe(t_node **node, t_command **cmd, char ***array, int *fd_in, int *fd_out) 
{
    t_command *response;
    if(!*node)
        return ;
    if (!ft_strncmp((*node)->type, "pipe", 4)) 
    {
        if (*array) 
        {
            response = ft_lstnew_cmd(*array, *fd_in, *fd_out);
            ft_lstadd_back_cmd(cmd, response);
            *array = NULL;
            *fd_out = 1;
            *fd_in = 0;
        }
        *node = (*node)->next;
    }
}

void handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
      if(!*node)
        return ;
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
    if(!*node)
        return ;
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

void execute_commands(t_command *cmd, t_node **env, t_node **addresses)
{
    t_command *tmp;
    char *path;
   int i = 0;
    tmp= cmd;
    path = getenv("PATH");
    while(tmp)
    {
        tmp = tmp->next;
        i++;
    }
    while(cmd) 
    {
        // if(!is_builtin(cmd, env, addresses))
        // {
            cmd->cmd = ft_pathname(path, cmd->cmd);
            make_process(cmd,env,  path);
        // }
        cmd = cmd->next;
    }
    while(i-- > 0)
        wait(NULL);
}
int check_builtin(char *command)
{
    if(strcmp(command, "/usr/bin/env") == 0)
        return (1);
    else if(strcmp(command, "/bin/pwd") == 0)
        return (1);
    else if(strcmp(command, "/bin/echo") == 0)
        return (1);
    // else if(strcmp(command, "unset") == 0)
    //     return (1);
    // else if(strcmp(command, "export") == 0)
    //     return (1);
    else if(strcmp(command, "/usr/bin/cd") == 0)
        return (1);
    return (0);
}

int exec_builtin(char **command, t_node **env)
{
    // puts("hello");
    if(!command || !*command)
        return (0);
    if(strcmp(command[0], "/usr/bin/env") == 0)
        return (exec_env(*env), 1);
    else if(strcmp(command[0], "/bin/pwd") == 0)
        return (exec_pwd(), 1);
    else if(strcmp(command[0], "/bin/echo") == 0)
        return (exec_echo(command, *env),1);
    // else if(strcmp(command[0], "unset") == 0)
    //     return ( 1);
    // else if(strcmp(command[0], "export") == 0)
    //     return (1);
    else if(strcmp(command[0], "/usr/bin/cd") == 0)
        return (exec_cd(command[1]),1);
    return (0);
}
void make_process(t_command *command,t_node **env,  char *path)
{
    int fd[2];
    int pid;
    if(command->next)
    {
        if(pipe(fd) == -1)
            perror("Error creating pipe");
    }
    int flag = 0;
    pid = fork();
    if(pid == -1)
        perror("Error forking");
    if(pid == 0)
    {
        if(check_builtin(command->cmd[0]))
            flag = 1;
        if(command->input != 0)
        {
            dup2(command->input, 0);
            close(command->input);
        }
        if ((command->next && command->output == 1) || flag == 1)
        {
            dup2(fd[1], 1);
            close(fd[1]);
            if(flag == 1)
            {               
                if(!exec_builtin(command->cmd, env))
                    return ;
                exit(0);
            }
        }
        else if(command->output != 1)
        {
            dup2(command->output, 1);
            close(command->output);
        }
        // puts(command->cmd[0]);
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
char	**ft_pathname(char *p, char **cmdargs)
{
	int		i;
	char	*cmd;
    char    **paths;

    paths = ft_split(p, ':');
    if(!paths || !cmdargs || !*cmdargs)
        return ( NULL);
	i = -1;
    if(cmdargs[0][0] == '/')
        return (cmdargs);
	while (paths[++i])
	{
		cmd = ft_join_free(paths[i], "/");
		cmd = ft_join_free(cmd, cmdargs[0]);
		if (access(cmd, F_OK | X_OK) == 0)
			break;
	}
    cmdargs[0] = cmd;
	return (cmdargs);
}
char	*ft_join_free(char *s, const char *buf)
{
	char	*r;

	r = ft_strjoin(s, buf);
	free(s);
	return (r);
}
t_command	*ft_lstnew_cmd(char **cmd, int input, int output)
{
	t_command	*ptr;

	ptr = (t_command *)malloc(sizeof(t_command));
	if (!ptr)
		return (NULL);
	ptr->cmd = cmd;
	ptr->input = input;
	ptr->output = output;
	ptr -> next = NULL;
	return (ptr);
}

t_command	*ft_lstlast_cmd(t_command *lst)
{
	t_command	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = ft_lstlast_cmd(*lst);
		ptr -> next = new;
	}
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