/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:37:52 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/14 03:49:11 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check(char *s, char c)
{
    while(*s)
    {
        if(*s == c)
            return (1);
        s++;
    }
    return (0);
}


void	free_array(char **array)
{
    int j;
    
    j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
}

void	ft_lstadd_front1(t_node **lst, t_node *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

t_node	*ft_lstnew1(void *value, char *type)
{
	t_node	*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->value = value;
	ptr -> next = NULL;
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

void	ft_lstadd_back1(t_node **lst, t_node *new)
{
	t_node	*ptr;

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
		ptr = ft_lstlast1(*lst);
		ptr -> next = new;
	}
}