/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:00:50 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/19 15:52:14 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_node **node, int *fd_out, int flag)
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

int	open_file1(t_node **node, t_fd *fd, char **env, t_node **addresses)
{
	t_node	*tmp;

	if (fd->flag)
	{
		fd->in = open((*node)->value, O_RDONLY, 0644);
		if (fd->in == -1)
			ft_putstr_fd("No such file or directory\n", 2);
		exit_status(1);
	}
	else
		fd->in = ft_herdoc(*node, env, addresses);
	if (fd->in == -1)
		exit_status(1);
	tmp = (*node)->next;
	while (tmp && !ft_strcmp(tmp->type, "space"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->type, "pipe"))
	{
		fd->in = open("k", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd->in == -1 || unlink("k") == -1)
			return (exit_status(1), 1);
	}
	*node = (*node)->next;
	return (0);
}

int	pipe_parse_error(t_node *node)
{
	t_node	*ptr;

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
				return (ft_putstr_fd("parse error near `|'\n", 2),
					exit_status(258), 1);
		}
		if (ptr)
			ptr = ptr -> next;
	}
	return (0);
}

t_command	*set_newlist(t_node **node, t_env *env, t_node **addresses)
{
	t_new_list	new;

	new.s = NULL;
	new.cmd = NULL;
	new.array = NULL;
	if (pipe_parse_error(*node))
		return (NULL);
	if (!hande_tokens(node, env, &new, addresses))
		return (NULL);
	new.array = ft_array(new.array, new.s, addresses);
	if (new.array && *new.array)
		ft_lstadd_back_cmd(&new.cmd, ft_lstnew_cmd(new.array,
				new.fd.in, new.fd.out, addresses));
	return (new.cmd);
}

char	**ft_array(char **array, char *s, t_node **addresses)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!array)
	{
		new = ft_malloc(sizeof(char *) * 2, addresses);
		if (!new)
			return (NULL);
		new[0] = s;
		new[1] = NULL;
		return (new);
	}
	while (array[i])
		i++;
	new = ft_malloc(sizeof(char *) * (i + 2), addresses);
	if (!new)
		return (NULL);
	while (array[++j])
		new[j] = array[j];
	new[j] = s;
	new[j + 1] = NULL;
	return (new);
}
