/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ayoub.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:23:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/19 17:14:05 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_parse_error(t_node *node)
{
	t_node *ptr; 

	ptr = node;
	while (ptr && !ft_strncmp(ptr->type, "space", 5))
		ptr = ptr -> next;
	if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
		return (ft_putstr_fd("parse error near `|'\n", 2), exit_status(258), 1);
	while (ptr)
	{
		if (ptr && !ft_strncmp(ptr->type, "pipe", 4))
		{
			ptr = ptr -> next;
			while (ptr && !ft_strncmp(ptr->type, "space", 5))
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
		if ((*new)->array && *(*new)->array)
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
	while (node)
	{   
		printf("input : %d\n", node->input);
		printf("output : %d\n", node->output);
		printf("cmd : [");
		i = 0;
		while (node && node->cmd && node->cmd[i])
		{
			printf("%s,", node->cmd[i]);
			i++;
		}
		printf("]\n");
		printf("\n");
		node = node->next;
	}
}

bool    hande_tokens(t_node **node, t_env *env, t_new_list *new, t_node **addresses)
{   
	new->fd.flag = 0;
	new->fd.in = 0;
	new->fd.out = 1;
	while (*node)
	{
		handle_space(node, &new->array, &new->s, addresses);
		handle_pipe(node, &new, &new->fd, addresses);
		if (handle_append_or_red_out(node, &new->fd.out, new->fd.flag))
			return (FALSE);
		if (handle_here_doc_or_rd_in(node, &new->fd, env->env,addresses))
			return (FALSE);
		if (*node && (!ft_strncmp((*node)->type, "pipe", 4) || !ft_strncmp((*node)->type, "space", 5)))
			continue ;
		if (*node)
		{
			expand(*node, env, addresses, NULL);
			new->s = ft_strjoin(new->s, (*node)->value, addresses);
			*node = (*node)->next;
		}
	}
	return TRUE;
}

t_command *set_newlist(t_node **node, t_env *env, t_node **addresses)
{
	t_new_list new;

	new.s = NULL;
	new.cmd = NULL;
	new.array = NULL;

	if (pipe_parse_error(*node))
		return (NULL);
	if (!hande_tokens(node, env, &new, addresses))
		return (NULL);
	new.array = ft_array(new.array, new.s, addresses);
	if (new.array && *new.array)
		ft_lstadd_back_cmd(&new.cmd, ft_lstnew_cmd(new.array, new.fd.in, new.fd.out, addresses));
	return (new.cmd);
}

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


int open_file(t_node **node, int *fd_out, int flag)
{
	if (flag)
		*fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		*fd_out = open((*node)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_out == -1)
			return (exit_status(1), 1);
	*node = (*node)->next;
	return (0);
}

int  handle_append_or_red_out(t_node **node, int *fd_out, int flag) 
{
	if (!*node)
		return (0);
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
			return (open_file(node, fd_out, flag), 0);
		else
			return (error_redirection(1), 1);
	}
	return (0);
}

int open_file1(t_node **node, t_fd *fd, char **env, t_node **addresses)
{
	t_node *tmp;
	
	if (fd->flag)
		fd->in = open((*node)->value, O_RDONLY, 0644);
	else
		fd->in = ft_herdoc(*node, env, addresses);
	if (fd->in == -1)
		ft_putstr_fd("No such file or directory\n", 2);
	tmp = (*node)->next;
	while (tmp && !ft_strcmp(tmp->type, "space"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->type, "pipe"))
	{
		fd->in = open("k", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd->in == -1 || unlink("k") == -1)
			return (1);
	}
			*node = (*node) -> next;
	return (0);
}

int handle_here_doc_or_rd_in(t_node **node, t_fd *fd, char **env, t_node **addresses)
{
	int	flag;
	int	*fd_in;
	fd_in = &fd->in;

	if (!*node)
		return (0);
	if (!ft_strncmp((*node)->type, "here_doc", 8)
		|| !ft_strncmp((*node)->type, "rd_in", 5)) 
	{
		fd->flag = 0;
		if (!ft_strncmp((*node)->type, "rd_in", 5))
			fd->flag = 1;
		*node = (*node)->next;
		while (*node && !ft_strncmp((*node)->type, "space", 5))
			*node = (*node)->next;
		if (!*node)
			return (error_redirection(0), 1);
		if (*node && (!ft_strncmp((*node)->type, "word", 4)
			|| !ft_strncmp((*node)->type + 2, "quote", 5)))
			return (open_file1(node, fd, env, addresses), 0);
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
	return (0);
}

int ft_wait(int size, int pid)
{
	int status;
	int g_pid;
	
	while (size--)
	{
		g_pid = wait(&status);
		if (g_pid == -1)
			return (1);
		if (g_pid == pid)
			exit_status(WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
			{
				write(1,"\n",1);
				exit_status(130);
			}
			else if (WTERMSIG(status) == 3)
			{
				ft_putendl_fd("Quit: 3", 2);
				exit_status(131);
			}
		}
	}
	return (0);
}

void check_errors_child(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (cmd[0] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else if (cmd[0] != '$')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(127);
}

int	make_process(t_command *cmd, t_env *env, int fd_out, int flag)
{
	int		fd[2];
	int		pid;
	char	*matching_path;

	if (pipe(fd) == -1)
		return (write(2, "pipe failed\n", 12), 0);
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 0);
	if (pid == 0)
	{
		signal_default();
		close(fd[0]);
		if (flag == 1 && dup2(fd_out, 1) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2),0);
		if (flag != 1 && dup2(fd[1], 1) == -1)
			return (ft_putstr_fd("dup2 failed\n", 2),0);
		close(fd[1]);
		if (!is_builtin(cmd, env, NULL))
		{
			execve(cmd->cmd[0], cmd->cmd, env->env);
			check_errors_child(cmd->cmd[0]);
		}
		exit(0);
	}
	if (dup2(fd[0], 0) == -1)
		return (ft_putstr_fd("dup2 failed\n", 2), 0);
	(close(fd[1]), close(fd[0]));
	return (pid);
}
char	*test_execution(char **paths, char **command, char **matching_path)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (paths && paths[i] && command[0] && command[0][0] != '\0')
	{
		if (command[0][0] != '/')
		{
			temp = ft_strjoin(paths[i], "/", NULL);
			if (temp == NULL)
				return (NULL);
			*matching_path = ft_strjoin(temp, *command, NULL);
			if (*matching_path == NULL)
				return (free(temp), NULL);
		}
		else
			*matching_path = ft_strdup(*command, NULL);
		free(temp);
		if (!access(*matching_path, X_OK) || !*matching_path)
			return (*matching_path);
		free(*matching_path);
		i++;
	}
	return (NULL);
}
int loop_process(t_command *command, t_env *env, t_node **addresses) 
{
	int fd[2];
	int i = 0;
	char *path;
	// while(command)
	// {
	// display_cmd(command);
	// command = command->next;
	
	// }
	// exit(0);
	run_signals(0);
	if (!command)
		return (0);
	int size = ft_lstsize_cmd(command);
	path = get_environment(env->env, "PATH", addresses);
	if (dup2(command->input, 0) == -1)
		return (write(2, "dup2 failed\n", 12), 0);
	while (command->next)
	{
		if (!builtin_key(command, addresses))
			command->cmd = ft_pathname(path, command->cmd, env->env, addresses);
		make_process(command, env,command->output , 0);
		command = command->next;
		i++;
	}
	if (i == 0 && is_builtin(command, env, addresses))
		return (1);
	if (!builtin_key(command, addresses))
		command->cmd = ft_pathname(path, command->cmd, env->env, addresses);
	int pid = make_process(command, env,command->output, 1);
	if (ft_wait(size, pid))
	   exit_status(1);
	return (0);
}

void signal_here_doc(int sig)
{
	(void)(sig);
	write(1,"\n",1);
		exit(1);
}

void  ft_read_input(t_node *node, t_heredoc *heredoc, char **env, t_node **addresses)
{
	char *line;
	char *tmp = NULL;
	
	signal(SIGINT, signal_here_doc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, node->value))
		{
			free(line);
			break;
		}
		if (ft_strcmp("quote", node->type + 2))
			tmp = expand_heredoc(line, env, addresses);
		else
			tmp = line;
		tmp = ft_strjoin(tmp, "\n", addresses);
		write(heredoc->fd_write, tmp, ft_strlen(tmp));
		free(line);
	}
	close(heredoc->fd_write);
	close(heredoc->fd_read);
}
int ft_herdoc(t_node *node, char **env, t_node **addresses)
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
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_read_input(node, &heredoc, env, addresses);
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

char *request_env(char **envp, char *var)
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

char	*get_environment(char **envp, char *var, t_node **addresses)
{
	char *tmp;
	char *response;

	tmp  = NULL;
	response = NULL;
	tmp = ft_strjoin(var, "=", addresses);
	if (!tmp)
		return (NULL);
	response = request_env(envp, tmp);
	if (!response)
	{
		tmp = ft_strjoin(var, "+=", addresses);
		response = request_env(envp, tmp);
	}
	return (response);
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
	if (cmdargs[0][0] == '/' || cmdargs[0][0] == '.')
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

char	**ft_ft_array(char **array, char *s)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!array)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = s;
		new[1] = NULL;
		return (new);
	}
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	while (array[++j])
		new[j] = array[j];
	new[j] = ft_ft_strdup(s);
	new[j + 1] = NULL;
	return (free(array), new);
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