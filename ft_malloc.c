#include "minishell.h"

void smart_free(t_node *adresses)
{
    t_node *tmp;

    while (adresses)
    {
        tmp = adresses;
        adresses = adresses->next;
        free(tmp->value);
        free(tmp);
    }
}
static void *add_node(t_node *adresses, void *value)
{
    t_node *new;
    t_node *tmp;

    new = malloc(sizeof(t_node));
    if (new == NULL)
        return (smart_free(adresses), NULL);
    new->next = NULL;
    new->value = value;
    tmp = adresses;
    while(tmp)
        tmp = tmp->next;
    tmp = new;
    return (new);
}

int ft_malloc(int size, void **response, t_node **adresses)
{
    void *value;
    value = malloc(size);
    if (value == NULL)
        return(smart_free(*adresses), 0);
    if(!add_node(*adresses, value))
        return(0);
    *response = value;
    return (1);
}
