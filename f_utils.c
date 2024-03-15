/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:37:52 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/15 04:17:23 by aben-cha         ###   ########.fr       */
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



t_command	*ft_lstnew_cmd(char *cmd, int input, int output)
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

// int check_command(char *s, t_node *node)
// {
//     char **array; 
//     // t_node *new;
//     // char *tmp;
//     // char *tmp2;
//     if (!ft_check(s, '|'))
//         return (1);
//     array = ft_split(s, '|');
//     if (!array)
//         return (1);
//     int i = 0;
//     int j;
//     int k = 0;
//     while(array[i])
//     {
//         // < Makefile grep cc |  ls -la
//         // 0123456789
//         if(array[i][0] == '<')
//         {
//             j = 1;
//             while(array[i][j] == ' ')
//                 j++;
//             k = j;
//             while(array[i][k] != ' ')
//                 k++;
//             // tmp = ft_substr(array[i], 0, k);
//             // new = ft_lstnew1(tmp, "word");
//             // if (!new)
//             //     return (free(s), free_array(array), free(tmp), 1);
//             // ft_lstadd_back1(&node, new);
//             // printf("\ntmp : %s\n", tmp);
//             node = fill_list_commands(node, array[i], 0, k);

//             while(array[i][k] == ' ')
//                 k++;
            
//             // tmp2 = ft_substr(array[i], k, ft_strlen(array[i]));
//             // new = ft_lstnew1(tmp2, "word");
//             // if (!new)
//             //     return (free(s), free_array(array), free(tmp2), 1);
//             // ft_lstadd_back1(&node, new);
//             // printf("tmp2 : %s\n", tmp2);
//             node = fill_list_commands(node, array[i], k, ft_strlen(array[i]));


//         }
//         i++;
//     }
//     printf("---------node :-------\n");
//     display(node);
//     printf("-----------------------\n");
//     free_array(array);
//     return (0);
// }

