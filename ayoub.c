/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ayoub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:23:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/20 12:13:50 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_parse_error(t_node *node)
{
    t_node *ptr; 

    ptr = node;
    while(ptr && !ft_strncmp(ptr->type, "space", 5))
        ptr = ptr -> next;
    if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
    {
        printf("parse error near `|'\n");
        return 1;
    }
    while (ptr)
    {
        if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
        {
            ptr = ptr -> next;
            while(ptr && !ft_strncmp(ptr->type, "space", 5))
                ptr = ptr -> next;
            if(!ptr || !ft_strncmp(ptr->type, "pipe", 4))
            {
                printf("parse error near `|'\n");
                return 1;
            }
        }
        if(ptr)
            ptr = ptr -> next;
    }
    return 0;
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

    if (pipe_parse_error(*node))
        return (NULL);
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
    if(array && *array)
        ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd_in, fd_out));
    return (cmd);
}



void handle_space(t_node **node, char ***array, char **s) 
{
    if (!*node)
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
        if (*array && **array) 
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
        while (*node && !ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (*node && (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type, "quote", 5))) 
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
    if (!*node)
        return ;
    if (!ft_strncmp((*node)->type, "here_doc", 8) || !ft_strncmp((*node)->type, "rd_in", 5)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "rd_in", 5))
            flag = 1;
        if((*node)->next)
        {
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
        }
        else
            perror("");
    }
}

int check_builtin(char *command)
{
    if(!command)
        return (0);
    if(ft_strncmp(command, "/usr/bin/env", 12) == 0)
        return (1);
    else if(ft_strncmp(command, "/bin/pwd", 8) == 0)
        return (1);
    else if(ft_strncmp(command, "/bin/echo", 9) == 0)
        return (1);
    else if(ft_strncmp(command, "/usr/bin/cd", 11) == 0)
        return (1);
    return (0);
}

int exec_builtin(char **command, char **env)
{
    if(!command)
        return (0);
    if(ft_strncmp(command[0], "/usr/bin/env", 12) == 0)
        return (exec_env(env), 1);
    else if(ft_strncmp(command[0], "/bin/pwd", 8) == 0)
        return (exec_pwd(), 1);
    else if(ft_strncmp(command[0], "/bin/echo", 9) == 0)
        return (exec_echo(command, env),1);
    else if(ft_strncmp(command[0], "/usr/bin/cd", 11) == 0)
        return (exec_cd(command[1]),1);
    return (0);
}
void execute_commands(t_command *cmd, char ***env,char ***export_env, t_node **addresses)
{
    char *path;
    int pid = 0;
    // int size = ft_lstsize_cmd(cmd);
    path = get_environment(*env, "PATH=");
    while(cmd) 
    {
        // if(is_builtin(cmd, env, export_env, addresses))// && szie == 1)
            // break;
        // else 
        if(!is_builtin(cmd, env, export_env, addresses))
        {
            cmd->cmd = ft_pathname(path, cmd->cmd, *env);
            make_process(cmd,*env,  path, &pid);
        }
        cmd = cmd->next;
    }
    int status;
    int g_pid;

    // if(size == 1 && is_builtin(cmd, env, export_env, addresses))
        // return ;
    // while (size--)
    // {
    //     printf("test\n");
        
    //     g_pid = wait(&status);
    //     if(g_pid == -1)
    //     {
    //         printf("Errno(error wait)\n");
    //         return ;
    //     }
    //     if(g_pid == pid)
    //         get_exit_status = WEXITSTATUS(status);
    //     if(WIFSIGNALED(status))
    //     {
    //         if(WTERMSIG(status) == 2) // (WTERMSIG(status) == SIGINT)
    //             get_exit_status = 130;
    //         else if(WTERMSIG(status) == 3)// (WTERMSIG(status) == SIGQUIT)
    //             get_exit_status = 131;
    //     }
    // }

    while (wait(NULL)>0);
}
int make_process(t_command *command, char **env, char *path, int *i)
{
    int fd[2];
    int pid;
    int flag  = 0;
    int response = 0;
    if(!command->cmd)
        return 0;
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
        if(check_builtin(command->cmd[0]))
            flag = 1;
        if(command->input != 0)
        dup2(command->input, 0);
        if(command->input != 0)
            close(command->input);
        if(command->next && command->output == 1 || flag == 1)
        {
            dup2(fd[1], 1);
            close(fd[1]);
            if(flag == 1)
            {
                if(!exec_builtin(command->cmd , env))
                    exit(1);
                exit(0);
            }
        }
        else if(command->output != 1)
        {
            dup2(command->output, 1);
            close(command->output);
        }
        response = execve(command->cmd[0], command->cmd,env);
    }
    else
    {
        //()
        *i = pid;
        close(fd[1]);
        command = command->next;
        if(command)
            command->input = fd[0];
        else
            close(fd[0]);
    }
    return 0;
}

int ft_herdoc(char *s)
{
    int fd[2];
    char *line;
    char *tmp;
    pipe(fd);
    while(1)
    {
        line = readline("heredoc> ");
        if(!line)
            break;
        if(!ft_strncmp(line, s, ft_strlen(s)) && ft_strlen(line) == ft_strlen(s))
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
char	**ft_pathname(char *p, char **cmdargs, char **env)
{
	int		i;
	char	*cmd;
    char    **paths;

    paths = ft_split(p, ':');
    if(!cmdargs || !*cmdargs)
        return ( NULL);
	i = -1;
    if(cmdargs[0][0] == '/' )//|| is_builtin())
        return (cmdargs);
	while (paths && paths[++i])
	{
		cmd = ft_join_free(paths[i], "/");
		cmd = ft_join_free(cmd, cmdargs[0]);
		if (access(cmd, F_OK | X_OK) == 0)
        {
            cmdargs[0] = cmd;
            return (cmdargs);
        }
	}
    printf("command not found\n");
	return (NULL);
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

int	ft_lstsize_cmd(t_command *cmd)
{
	int		len;
	t_command	*ptr;

	if (!cmd)
		return (0);
	len = 0;
	ptr = cmd;
	while (ptr)
	{
		len++;
		ptr = ptr -> next;
	}
	return (len);
}