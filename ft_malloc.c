#include "minishell.h"

void    free_addresses(t_node *addresses)
{
    t_node *tmp;

    while (addresses)
    {
        tmp = addresses;
        addresses = addresses->next;
        free(tmp->value);
        free(tmp);
    }
}

int ft_malloc(size_t size, void **ptr, t_node **addresses)
{
    *ptr = malloc(size);
    if(!*ptr)
    {
        free_addresses(*addresses);
        return 0;
    }
    add_back(addresses, ft_alloc(ptr, NULL));
    return 1;
}

t_node	*ft_alloc(void **value, char *type)
{
	t_node	*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->value = *value;
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
