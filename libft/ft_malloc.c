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

int ft_malloc(size_t size, void **ptr, void *addresses)
{
    *ptr = malloc(size);
    if(!*ptr)
    {
        free_addresses(addresses);
        return 0;
    }
    add_back(addresses, ft_alloc(*ptr, "malloc"));
    return 1;
}
