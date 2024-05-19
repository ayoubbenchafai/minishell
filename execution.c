/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:08:06 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/19 19:27:10 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		return ;
	close(fd[0]);
}

int	make_process(t_command *cmd, t_env *env, int fd_out, int flag)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		signal_default();
		close(fd[0]);
		if (flag == 1 && dup2(fd_out, 1) == -1)
			return (0);
		if (flag != 1 && dup2(fd[1], 1) == -1)
			return (0);
		close(fd[1]);
		if (!is_builtin(cmd, env, NULL))
		{
			execve(cmd->cmd[0], cmd->cmd, env->env);
			check_errors_child(cmd->cmd[0]);
		}
		exit(0);
	}
	return (parent_process(fd), pid);
}

int	loop_process(t_command *command, t_env *env, t_node **addresses)
{
	int		i;
	char	*path;
	int		size;
	int		pid;

	i = 0;
	run_signals(0);
	if (!command)
		return (0);
	size = ft_lstsize_cmd(command);
	path = get_environment(env->env, "PATH", addresses);
	if (dup2(command->input, 0) == -1)
		return (0);
	while (command->next)
	{
		if (!builtin_key(command, addresses))
			command->cmd = ft_pathname(path, command->cmd, addresses);
		make_process(command, env, command->output, 0);
		command = command->next;
		i++;
	}
	if (i == 0 && is_builtin(command, env, addresses))
		return (1);
	if (!builtin_key(command, addresses))
		command->cmd = ft_pathname(path, command->cmd, addresses);
	pid = make_process(command, env, command->output, 1);
	if (ft_wait(size, pid))
		exit_status(1);
	return (0);
}

char	**ft_pathname(char *p, char **cmdargs, t_node **addresses)
{
	int		i;
	char	*cmd;
	char	**paths;

	paths = ft_split(p, ':', addresses);
	if (!paths)
		return (cmdargs);
	if (!cmdargs || !*cmdargs)
		return (NULL);
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
