/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:05 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/20 16:12:55 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*ft_lstnew_cmd(char **cmd, int input, int output, t_node **addr)
{
	t_command	*ptr;

	ptr = ft_malloc(sizeof(t_command), addr);
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

t_node	*ft_lstnew1(void *value, char *type, t_node **addresses)
{
	t_node	*ptr;

	ptr = ft_malloc(sizeof(t_node), addresses);
	if (!ptr)
		return (NULL);
	ptr->type = ft_malloc(sizeof(char) * (ft_strlen(type) + 1), addresses);
	if (!ptr->type)
		return (NULL);
	ptr->value = ft_malloc(sizeof(char) * (ft_strlen(value) + 1), addresses);
	if (!ptr->value)
		return (NULL);
	ft_strlcpy(ptr->type, type, ft_strlen(type) + 1);
	ft_strlcpy(ptr->value, value, ft_strlen(value) + 1);
	ptr->next = NULL;
	return (ptr);
}

void	ft_lstadd_back1(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (!new)
		return ;
	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = ft_lstlast1(*lst);
		ptr -> next = new;
	}
}
