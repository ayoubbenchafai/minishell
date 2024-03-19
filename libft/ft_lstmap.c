/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:34:35 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/10 23:44:06 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*head;
	void	*content;

	new_node = NULL;
	head = NULL;
	while (lst && f && del)
	{
		content = f(lst->content);
		if (content == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			ft_lstclear(&head, del);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		lst = lst->next;
	}
	return (head);
}

// void *fun(void *content)
// {
//     return "brahim_weld_jdida";
// }
// int main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	t_list	*head;
// 	t_list *tmp;

// 	node1 = ft_lstnew("a");
// 	node2 = ft_lstnew("b");
// 	node3 = ft_lstnew("c");
// 	ft_lstadd_front(&node2,node1);
// 	ft_lstadd_back(&node2,node3);
// 	head = ft_lstmap(node1, fun, free);
// 	while (head)
//     {
//         printf("%s", (char *)head->content);
//         tmp = head;
//         head = head->next;
//         free(tmp);
//     }
// }