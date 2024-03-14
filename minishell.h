/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:55:11 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/14 03:33:49 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node
{
    void    *value;
    char    *type;
    struct s_node   *next;
}           t_node;


void	ft_lstadd_front1(t_node **lst, t_node *new);
t_node	*ft_lstnew1(void *value, char *type);
t_node	*ft_lstlast1(t_node *lst);
void	ft_lstadd_back1(t_node **lst, t_node *new);
void	free_array(char **array);
int     ft_check(char *s, char c);

#endif