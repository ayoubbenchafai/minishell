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

	ptr = NULL;
	ft_malloc(sizeof(t_node), (void **)&ptr, addresses);
	if (!ptr)
		return (NULL);
	ft_malloc(sizeof(char) * (ft_strlen(type) + 1), (void **)&ptr->type, addresses);
	ft_malloc(sizeof(char) * (ft_strlen(value) + 1), (void **)&ptr->value, addresses);
	ft_strlcpy(ptr->type, type, ft_strlen(type) + 1);
	ft_strlcpy(ptr->value, value, ft_strlen(value) + 1);
	ptr -> next = NULL;
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
