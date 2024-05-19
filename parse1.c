/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:58:19 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/19 15:50:48 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_node **node, char ***array, char **s, t_node **addresses)
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

void	handle_pipe(t_node **node, t_new_list **new, t_fd *fd, t_node **addr)
{
	t_command	*response;

	if (!*node)
		return ;
	if (!ft_strncmp((*node)->type, "pipe", 4))
	{
		if ((*new)->array && *(*new)->array)
		{
			response = ft_lstnew_cmd((*new)->array, (*new)->fd.in,
					(*new)->fd.out, addr);
			ft_lstadd_back_cmd(&(*new)->cmd, response);
			(*new)->array = NULL;
			(*new)->fd.out = 1;
			(*new)->fd.in = 0;
		}
		*node = (*node)->next;
	}
}

int	handle_here_doc_or_rd_in(t_node **node, t_fd *fd, char **env, t_node **addr)
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
			return (open_file1(node, fd, env, addr), 0);
		else
			return (error_redirection(2), 1);
	}
	return (0);
}

int	handle_append_or_red_out(t_node **node, int *fd_out, int flag)
{
	if (!*node)
		return (0);
	if (!ft_strncmp((*node)->type, "append", 6)
		|| !ft_strncmp((*node)->type, "rd_out", 6))
	{
		flag = 0;
		if (!ft_strncmp((*node)->type, "append", 6))
			flag = 1;
		*node = (*node)->next;
		while (*node && !ft_strncmp((*node)->type, "space", 5))
			*node = (*node)->next;
		if (!*node)
			return (error_redirection(0), 1);
		if (*node && (!ft_strncmp((*node)->type, "word", 4)
				|| !ft_strncmp((*node)->type + 2, "quote", 5)))
			return (open_file(node, fd_out, flag), 0);
		else
			return (error_redirection(1), 1);
	}
	return (0);
}

bool	hande_tokens(t_node **node, t_env *env, t_new_list *new, t_node **addr)
{
	new->fd.flag = 0;
	new->fd.in = 0;
	new->fd.out = 1;
	while (*node)
	{
		handle_space(node, &new->array, &new->s, addr);
		handle_pipe(node, &new, &new->fd, addr);
		if (handle_append_or_red_out(node, &new->fd.out, new->fd.flag))
			return (FALSE);
		if (handle_here_doc_or_rd_in(node, &new->fd, env->env, addr))
			return (FALSE);
		if (*node && (!ft_strncmp((*node)->type, "pipe", 4)
				|| !ft_strncmp((*node)->type, "space", 5)))
			continue ;
		if (*node)
		{
			expand(*node, env, addr, NULL);
			new->s = ft_strjoin(new->s, (*node)->value, addr);
			*node = (*node)->next;
		}
	}
	return (TRUE);
}
