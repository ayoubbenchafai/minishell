/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:22 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/20 15:06:47 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_addresses(t_node *addresses)
{
    t_node *tmp;

    while (addresses)
    {
        tmp = addresses;
        addresses = addresses->next;
		// printf("freeing internal ptr : %s\n", tmp->value);
        free(tmp->value);
		// printf("freeing external node : %p\n", tmp);
        free(tmp);
    }
}

void *ft_malloc(size_t size, t_node **addresses)
{
	void *ptr = malloc(size);
    if(!ptr)
    {
        // free_addresses(*addresses);
        return NULL;
    }
    add_back(addresses, ft_alloc(ptr, NULL));
    return ptr;
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
	if(!lst)
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
