/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:23:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/18 20:09:36 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_key(t_command *cmd, t_node **addresses)
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

int	ft_wait(int size, int pid)
{
	int	status;
	int	g_pid;

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
				write(1, "\n", 1);
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

void	get_terminal_attr(struct termios *original_termios)
{
	tcgetattr(STDIN_FILENO, original_termios);
	original_termios->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

void	restore_terminal_attributes(struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
