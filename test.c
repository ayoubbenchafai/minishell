/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:11:58 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/17 01:32:36 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#includ "libft/libft.h"

t_node *get_node(t_node *nodes)
{
    ft_lstadd_back1(&nodes, ft_lstnew1("l", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-l", "squote"));
    ft_lstadd_back1(&nodes, ft_lstnew1("a", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("grep", "dquote"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1("s", "squote"));


    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("echo", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-n", "squote"));

    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));
    ft_lstadd_back1(&nodes, ft_lstnew1("$PATH", "expand"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "space"));

    ft_lstadd_back1(&nodes, ft_lstnew1(">>", "append"));
    ft_lstadd_back1(&nodes, ft_lstnew1("file", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("|", "pipe"));
    ft_lstadd_back1(&nodes, ft_lstnew1("cat", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1(" ", "word"));
    ft_lstadd_back1(&nodes, ft_lstnew1("-e", "sqoute"));
    return nodes;
}

char **ft_array(char **array, char *s)
{
    char **new;
    int i;
    int j;

    i = 0;
    j = 0;
    if (!array)
    {
        new = (char **)malloc(sizeof(char *) * 2);
        new[0] = s;
        new[1] = NULL;
        return new;
    }
    else
    {
        while (array[i])
            i++;
        new = (char **)malloc(sizeof(char *) * (i + 2));
    }
    while (array[j])
    {
        new[j] = array[j];
        j++;
    }
    new[j] = s;
    new[j + 1] = NULL;
    free(array);
    return new;
}

void set_newlist(t_node *node) 
{
    t_command *cmd = NULL;
    t_command *new;
    char *s = NULL;
    while (node) 
    {
        if (!ft_strncmp(node->type, "space", 5))
        {
            array = ft_array(array, s);
            free(s);
            s = NULL;
        }
        if (!ft_strncmp(node->type, "pipe", 4))
        {
            ft_lstadd_back_cmd(&cmd, ft_lstnew_cmd(array,0,1));
            array = NULL;
        }
        s = ft_strjoin(s, node->value);
        node = node->next;
    }
    ft_lstadd_back_cmd(&cmd, new);

    printf("-------------commands------------\n");
    display_cmd(cmd);
    printf("-------------fin commands-------------\n");
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
		return (lst);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back_cmd(t_command **lst, t_command *new)
{
	t_command	*ptr;

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

void display_cmd(t_command *cmd)
{
    int i;
    while(cmd)
    {   
        printf("input : %d\n", cmd->input);
        printf("output : %d\n", cmd->output);
        printf("cmd : [");
        i = 0;
            while(cmd->cmd[i])
            {
                printf("%s,", cmd->cmd[i]);
                i++;
            }
        printf("]\n");
        printf("\n");
        cmd = cmd->next;
    }
}
int main()
{
    t_node *nodes = NULL;
    t_command *cmd = NULL;
    nodes = get_node(nodes);
    set_newlist(nodes);
    return 0;
}