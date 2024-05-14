/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ayoub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:23:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/14 15:27:14 by aben-cha         ###   ########.fr       */
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
        return (ft_putstr_fd("parse error near `|'\n", 2), exit_status(258), 1);
    while (ptr)
    {
        if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
        {
            ptr = ptr -> next;
            while(ptr && !ft_strncmp(ptr->type, "space", 5))
                ptr = ptr -> next;
            if (!ptr || !ft_strncmp(ptr->type, "pipe", 4))
                return (ft_putstr_fd("parse error near `|'\n", 2), exit_status(258), 1);
        }
        if (ptr)
            ptr = ptr -> next;
    }
    return (0);
}


void handle_space(t_node **node, char ***array, char **s, t_node **addresses)
{
    if (!*node)
        return ;
    if (!ft_strncmp((*node)->type, "space", 5))
    {
        *array = ft_array(*array, *s, addresses);
        *s = NULL;
        *node = (*node)->next;
    }
    else if (!ft_strncmp((*node)->type, "pipe", 4))
    {
        *array = ft_array(*array, *s, addresses);
        *s = NULL;
    }
}

void handle_pipe(t_node **node, t_new_list **new, t_fd *fd, t_node **addresses)
{
    t_command *response;
    
    if (!*node)
        return ;
    if (!ft_strncmp((*node)->type, "pipe", 4)) 
    {
        if((*new)->array && *(*new)->array)
        {
            response = ft_lstnew_cmd((*new)->array, (*new)->fd.in, (*new)->fd.out, addresses);
            ft_lstadd_back_cmd(&(*new)->cmd, response);
            (*new)->array = NULL;
            (*new)->fd.out = 1;
            (*new)->fd.in = 0;
        }
        *node = (*node)->next;
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


void hande_tokens(t_node **node, t_env *env, t_new_list *new, t_node **addresses)
{   
    new->fd.flag = 0;
    new->fd.in = 0;
    new->fd.out = 1;
    while (*node)
    {
        handle_space(node, &new->array, &new->s, addresses);
        handle_pipe(node, &new, &new->fd, addresses);
        if (handle_append_or_red_out(node, &new->fd.out, new->fd.flag))
            break;
        if (handle_here_doc_or_rd_in(node, &new->fd, env->env,addresses))
            break;
        if (*node && (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5)))
            continue ;
        if (*node)
        {
            expand(*node, env, addresses, NULL);
            new->s = ft_strjoin(new->s, (*node)->value, addresses);
            *node = (*node)->next;
        }
    }
}
t_command *set_newlist(t_node **node, t_env *env, t_node **addresses)
{
    t_new_list new;

    new.s = NULL;
    new.cmd = NULL;
    new.array = NULL;

    if (pipe_parse_error(*node))
        return (NULL);
    hande_tokens(node, env, &new, addresses);
    new.array = ft_array(new.array, new.s, addresses);
    if (new.array && *new.array)
        ft_lstadd_back_cmd(&new.cmd, ft_lstnew_cmd(new.array, new.fd.in, new.fd.out, addresses));
    return (new.cmd);
}

// t_command *set_newlist(t_node **node, t_env *env, t_node **addresses)
// {
//     t_fd        fd;
//     char        *s;
//     char        **array;
//     t_command   *cmd;
//     int         flag; 
//     cmd = NULL;
//     s = NULL;
//     array = NULL;
//     flag = 0;
//     fd.out = 1;
//     fd.in = 0;
//     if (pipe_parse_error(*node))
//         return (NULL);
//     while (*node) 
//     {
//         handle_space(node, &array, &s, addresses);
//         handle_pipe(node, &cmd, &array, &fd, addresses);
//         if (handle_append_or_red_out(node, &fd.out, flag))
//             break;
//         if (handle_here_doc_or_rd_in(node, &fd.in, flag, env, addresses))
//             break;
//         if (*node && (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5)))
//             continue ;
//         if (*node)
//         {
//             expand(*node, env, addresses);
//             s = ft_strjoin(s, (*node)->value, addresses);
//             *node = (*node)->next;
//         }
//     }
//     array = ft_array(array, s, addresses);
//     if (array && *array)
//         ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array, fd.in, fd.out, addresses));
//     return (cmd);
// }
 void error_redirection(int flag)
 {
    if (flag == 0)
        ft_putstr_fd("syntax error near unexpected token `newline'\n", 2); 
    else if (flag == 1)
        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
    else if (flag == 2)
        ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
    exit_status(258);
    return ;
 }

int  handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
    if (!*node)
        return (1);
    if (!ft_strncmp((*node)->type, "append", 6) || !ft_strncmp((*node)->type, "rd_out", 6)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "append", 6))
            flag = 1;
        *node = (*node)->next;
        while (*node && !ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (!*node)
            return (error_redirection(0), 1);
        if (*node && (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type + 2, "quote", 5))) 
        {
            if (flag)
            {
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
                if (*fd_out == -1)
                    return (exit_status(1), 1);
            }
            else
            {
                *fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if(*fd_out == -1)
                    return (exit_status(1), 1);
            }
            *node = (*node)->next;
        } 
        else
            return (error_redirection(1), 1);
    }
    return (0);
}

int handle_here_doc_or_rd_in(t_node **node, t_fd *fd, char **env, t_node **addresses)
{
    int flag = fd->flag;
    int *fd_in = &fd->in;
    if (!*node)
        return (1);
    if (!ft_strncmp((*node)->type, "here_doc", 8) || !ft_strncmp((*node)->type, "rd_in", 5)) 
    {
        flag = 0;
        if (!ft_strncmp((*node)->type, "rd_in", 5))
            flag = 1;
        *node = (*node)->next;
        while (*node && !ft_strncmp((*node)->type, "space", 5))
            *node = (*node)->next;
        if (!*node)
            return (error_redirection(0), 1);
        if (*node && (!ft_strncmp((*node)->type, "word", 4) || !ft_strncmp((*node)->type + 2, "quote", 5)))
        {
            if (flag)
            {
                *fd_in = open((*node)->value, O_RDONLY, 0644);
                if (*fd_in == -1)
                    ft_putstr_fd("No such file or directory\n", 2);
                t_node *tmp = (*node)->next;
                while (tmp && !ft_strcmp(tmp->type, "space"))
                    tmp = tmp->next;
                if (tmp && !ft_strcmp(tmp->type, "pipe"))
                {
                    *fd_in = open("k", O_CREAT | O_RDWR | O_TRUNC, 0644);
                    unlink("k");
                }
            }
            else
            {
                *fd_in = ft_herdoc((*node)->value, env, addresses);
                if (*fd_in == -1)
                    return (exit_status(1), 1);
            }
            *node = (*node) -> next;
        }
        else
            return (error_redirection(2), 1);
    }
    return (0);
}
// builtin_key is a function that checks if the command is a builtin command 
int builtin_key(t_command *cmd, t_node **addresses)
{
    if (!ft_strcmp(cmd->cmd[0], "cd") || !ft_strcmp(cmd->cmd[0], "echo") 
        || !ft_strcmp(cmd->cmd[0], "pwd") || !ft_strcmp(cmd->cmd[0], "export") 
        || !ft_strcmp(cmd->cmd[0], "unset") || !ft_strcmp(cmd->cmd[0], "env") 
        || !ft_strcmp(cmd->cmd[0], "exit"))
        return (1);
    if (cmd->cmd[0][0] == '$')
        return (print_exit_status(cmd->cmd[0], 1, addresses), 1);
    return 0;
}

int ft_wait(int size, int pid)
{
	int status;
    int g_pid;
	
    while (size--)
    {
        g_pid = wait(&status);
        if(g_pid == -1)
            return (write(1, "Error in wait\n", 14), 1);
        if (g_pid == pid)
            exit_status(WEXITSTATUS(status));
        if (WIFSIGNALED(status))
        {
            if(WTERMSIG(status) == 2)
            {
                write(1,"\n",1);
                exit_status(130);
            }
            else if(WTERMSIG(status) == 3)
            {
                ft_putendl_fd("Quit: 3", 2);
                exit_status(131);
            }
        }
    }
    return (0);
}

void execute_commands(t_command *cmd, t_env *env, t_node **addresses)
{
    char	*path;
    int		i;
    int		pid;
    int 	size;

    // printf("-------------commands------------\n");
    // display_cmd(cmd);
    // printf("-------------fin commands-------------\n");
	i = 0;
	pid = 0;
	size = ft_lstsize_cmd(cmd);
    path = get_environment(env->env, "PATH=");
    while(cmd) 
    {
        if (!builtin_key(cmd, addresses))
            cmd->cmd = ft_pathname(path, cmd->cmd, env->env, addresses);
        if(i == 0 && !cmd->next && is_builtin(cmd, env, addresses))
            return ;
        make_process(cmd, env, &pid, addresses);
        cmd = cmd->next;
        i++;
    }
	// ft_wait(size, pid);
    while(wait(NULL) > 0);
}

void check_errors_child(char *cmd)
{
	if(cmd[0] == '.' && cmd[1] == '/')
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
    else if(cmd[0] == '/')
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": is a directory\n", 2);
        exit(126);
    }
    else if(cmd[0] != '$')
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    exit(127);
}

int child_process(t_command *cmd, t_env *env, int *fd, t_node **addresses) 
{
    signal_default();
	if (dup2(cmd->input, 0) == -1)
		return (1);
    if (cmd->input != 0)
        if (close(cmd->input) == -1)
			return (1);
    if (cmd->next && cmd->output == 1) 
	{
		if(dup2(fd[1], 1) == -1 || close(fd[1]) == -1)
			return (1);
    }
    else if (cmd->output != 1) 
	{
		if (dup2(cmd->output, 1) == -1 || close(cmd->output) == -1)
			return (1);
    }
    if (!is_builtin(cmd, env, addresses) && cmd->cmd[0][0] != '\0') 
	{
        execve(cmd->cmd[0], cmd->cmd,env->env);
        check_errors_child(cmd->cmd[0]);
    }
    exit(0);
}

void parent_process(t_command *command, int *i, int pid, int *fd) 
{
    *i = pid;
	if (close(fd[1]) == -1)
		return ;
    command = command -> next;
    if (command)
        command->input = fd[0];
    else
	{
		if (close(fd[0]) == -1)
			return ;
	}
}

int make_process(t_command *command, t_env *env, int *i, t_node **addresses) 
{
    int fd[2];
    int pid;

    pid = 1;
    run_signals(0);
    if(!command->cmd)
        return (1);
    if(command->next)
	{
		if (pipe(fd) == -1)
			return (1);	
	}
    if (command->input != -1)
	    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
	{
		if (child_process(command, env, fd, addresses))
			return (1);
	}
    else 
        parent_process(command, i, pid, fd);
    return (0);
}

void signal_here_doc(int sig)
{
    (void)(sig);
    write(1,"\n",1);
        exit(1);
}

void  ft_read_input(char *s, t_heredoc *heredoc, char **env, t_node **addresses)
{
    char *line;
    char *tmp = NULL;
    
    signal(SIGINT, signal_here_doc);
    while(1)
    {
        line = readline("> ");
        if(!line)
            break ;
        if(!ft_strcmp(line, s))
        {
            free(line);
            break;
        }
        // expand(line, addresses);
        tmp = expand_heredoc(line, env, addresses);
        // tmp = ft_strjoin(tmp, line, addresses);
        tmp = ft_strjoin(tmp, "\n", addresses);
        write(heredoc->fd_write, tmp, ft_strlen(tmp));
        free(tmp);
        free(line);
    }
    close(heredoc->fd_write);
    close(heredoc->fd_read);
}
int ft_herdoc(char *s, char **env, t_node **addresses)
{
    int         pid;
    int			status;
    t_heredoc   heredoc;
    heredoc.fd_write = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    heredoc.fd_read = open("here_doc", O_RDONLY, 0644);
    if (heredoc.fd_write == -1 || heredoc.fd_read == -1 || unlink("here_doc") == -1)
        return (-1);
    run_signals(0);
    pid = fork();
    if(pid == -1)
        return (-1);
    if(pid == 0)
    {
        ft_read_input(s, &heredoc, env, addresses);
        exit(0);
    }
    if (wait(&status) == -1)
        return (-1);
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 1)
            exit_status(1);
    }
    close(heredoc.fd_write);
    return (heredoc.fd_read);
}

void    get_terminal_attr(struct termios *original_termios)
{
    tcgetattr(STDIN_FILENO, original_termios);
    original_termios->c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
void    restore_terminal_attributes(struct termios *original_termios)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
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
char	**ft_pathname(char *p, char **cmdargs, char **env, t_node **addresses)
{
	int		i;
	char	*cmd;
    char    **paths;

    paths = ft_split(p, ':', addresses);
    if (!paths)
        return (cmdargs);
    if (!cmdargs || !*cmdargs)
        return ( NULL);
	i = -1;
    if(cmdargs[0][0] == '/' || cmdargs[0][0] == '.')
        return (cmdargs);
	while (paths && paths[++i] && cmdargs[0][0])
	{
		cmd = ft_join_free(paths[i], "/", addresses);
		cmd = ft_join_free(cmd, cmdargs[0], addresses);
		if (access(cmd, F_OK | X_OK) == 0)
        {
            cmdargs[0] = cmd;
            return (cmdargs);
        }
	}
	return (cmdargs);
}

char	*ft_join_free(char *s, const char *buf, t_node **addresses)
{
	char	*r;

	r = ft_strjoin(s, buf, addresses);
	return (r);
}

t_command	*ft_lstnew_cmd(char **cmd, int input, int output, t_node **addresses)
{
	t_command	*ptr;

    ptr = ft_malloc(sizeof(t_command), addresses);
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
char **ft_array(char **array, char *s, t_node **addresses)
{
    char **new;
    int i;
    int j;

    i = 0;
    j = -1;
    if (!array)
    {
        new = ft_malloc(sizeof(char *) * 2, addresses);
        if (!new)
            return NULL;
        new[0] = s;
        new[1] = NULL;
        return new;
    }
    while (array[i])
            i++;
    new = ft_malloc(sizeof(char *) * (i + 2), addresses);
    if (!new)
        return NULL;
    while (array[++j])
        new[j] = array[j];
    new[j] = s;
    new[j + 1] = NULL;
    return new;
}

int	ft_lstsize_cmd(t_command *cmd)
{
	int         len;
	t_command   *ptr;

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