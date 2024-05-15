/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:22 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/15 17:59:32 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_addresses(t_node *addresses)
{
	t_node	*tmp;

	while (addresses)
	{
		tmp = addresses;
		addresses = addresses->next;
		free(tmp->value);
		free(tmp);
	}
}

void	*ft_malloc(size_t size, t_node **addresses)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	add_back(addresses, ft_alloc(ptr, NULL));
	return (ptr);
}

t_node	*ft_alloc(void *value, char *type)
{
	t_node	*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->value = value;
	ptr->next = NULL;
	return (ptr);
}

t_node	*ft_lstlast1(t_node *lst)
{
	t_node	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	add_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (!lst)
		return ;
	if (!*lst)
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
