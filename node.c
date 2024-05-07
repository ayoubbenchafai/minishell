/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:05 by miguiji           #+#    #+#             */
/*   Updated: 2024/04/03 07:58:32 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *set_type(char *s)
{
    char *tmp;
    
    tmp = NULL;
    if(!ft_strncmp(s, "<<", 2))
        tmp =  "herdoc";
    else if(!ft_strncmp(s, ">>", 2))
        tmp = "output_redirection_append";
    else if(s[0] == '>')
        tmp = "output_redirection";
    else if(s[0] == '<')
        tmp = "input_redirection";
    else if(s[0] == '|' && s[1] == '\0')
        tmp = "pipe";
    else if(s[0] == '$' && s[1])
        tmp =  "expand";
    else
        tmp = "word";
    return (tmp);
}

t_node	*ft_lstnew1(void *value, char *type, t_node **addresses)
{
	t_node	*ptr;

	ptr = ft_malloc(sizeof(t_node), addresses);
	if (!ptr)
		return (NULL);
	ptr->type = ft_malloc(sizeof(char) * (ft_strlen(type) + 1), addresses);
	if(!ptr->type)
		return (NULL);
	ptr->value = ft_malloc(sizeof(char) * (ft_strlen(value) + 1), addresses);
	if(!ptr->value)
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
