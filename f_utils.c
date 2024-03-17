/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:37:52 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/16 17:37:59 by aben-cha         ###   ########.fr       */
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



t_command	*ft_lstnew_cmd(char **cmd, int input, int output)
{
	t_command	*ptr;

	ptr = (t_command *)malloc(sizeof(t_command));
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



// void set_newlist(t_node *node)
// {
//    t_node *head = NULL;
//     t_node *new;
//     char *s = NULL;
//     while(node)
//     {
//         if(ft_strncmp(node->value, "|", 1))
//         // if(!ft_strncmp(node->type, "word", 4) || !ft_strncmp(node->type, "squote", 6)
//         //   || !ft_strncmp(node->type, "dquote", 6) || !ft_strncmp(node->type, "space", 5) ||
//         //    !ft_strncmp(node->type, "expand", 6))
//         {
//             s = ft_strjoin(s, node->value);
//             printf("s : %s\n", s);
//         }
//         else if (!ft_strncmp(node->value, "|", 1))
//         {
//                 printf("---> s : %s\n", s);
                
//                 new = ft_lstnew1(s, "test"); 
//                 ft_lstadd_back1(&head, new);
//                 s = NULL;
//         }
//         node = node ->next;        
//     }
//     if (check_redirections(s))
//     {
//         int i = 0;
//         int k = 0;
//         while(s[i] == ' ')
//             i++;
//         k = i;
//         // while(check_redirections(&s[i]))
//         //     k++;
//         // char *tmp = ft_substr(s, i, k -1);
//         // new = ft_lstnew1(tmp, "test"); 
//         // ft_lstadd_back1(&head, new);
//         char *tmp1 = ft_substr(s, k, ft_strlen(s));
//         new = ft_lstnew1(tmp1, "test"); 
//         ft_lstadd_back1(&head, new);
//     }
//     else
//         ft_lstadd_back1(&head, ft_lstnew1(s, "cmd"));
//     printf("-------------commands------------\n");
//     display(head);
//     printf("-------------fin commands-------------\n");
// }


// void set_newlist(t_node *node)
// {
//    t_node *head = NULL;
//     t_node *new;
//     t_command *cmds = NULL;
//     char *s = NULL;
//     while(node)
//     {
//         if(ft_strncmp(node->value, "|", 1))
//             s = ft_strjoin(s, node->value);
//             // printf("s : %s\n", s);
//         else if (!ft_strncmp(node->value, "|", 1))
//         {
//                 printf("---> s : %s\n", s);
                
//                 new = ft_lstnew1(s, "cmd"); 
//                 ft_lstadd_back1(&head, new);
//                 s = NULL;
//         }
//         node = node ->next;        
//     }
//     ft_lstadd_back1(&head, ft_lstnew1(s, "cmd"));
    
//     printf("-------------commands------------\n");
//     display(head);
//     printf("-------------fin commands-------------\n");
// }
