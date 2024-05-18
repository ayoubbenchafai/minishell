/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:22:45 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 18:30:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_here_doc(int sig)
{
	(void)(sig);
	write(1, "\n", 1);
	exit(1);
}

void	ft_read_input(t_node *node, t_heredoc *hd, char **env, t_node **addr)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	signal(SIGINT, signal_here_doc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, node->value))
		{
			free(line);
			break ;
		}
		if (ft_strcmp("quote", node->type + 2))
			tmp = expand_heredoc(line, env, addr);
		else
			tmp = line;
		tmp = ft_strjoin(tmp, "\n", addr);
		write(hd->fd_write, tmp, ft_strlen(tmp));
		free(line);
	}
	close(hd->fd_write);
	close(hd->fd_read);
}

int	ft_herdoc(t_node *node, char **env, t_node **addresses)
{
	int			pid;
	int			status;
	t_heredoc	hd;

	hd.fd_write = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	hd.fd_read = open("here_doc", O_RDONLY, 0644);
	if (hd.fd_write == -1 || hd.fd_read == -1 || unlink("here_doc") == -1)
		return (-1);
	run_signals(0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		(ft_read_input(node, &hd, env, addresses), exit(0));
	if (wait(&status) == -1)
		return (-1);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			exit_status(1);
	}
	close(hd.fd_write);
	return (hd.fd_read);
}
