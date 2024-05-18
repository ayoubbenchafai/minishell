/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:59:24 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 18:00:02 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expand(t_node *node, t_env *env, t_node **addresses, char *response)
{
    char *var;
    int i;
    int x;

    x = 0;
    i = 0;
    if (!node || !ft_strcmp(node->type, "s_quote"))
        return ;
    while(node->value && ((char *)node->value)[i])
    {
        while(((char *)node->value)[i] != '\0')
        {
            if (((char *)node->value)[i] == '$' && ft_isalnum(((char *)node->value)[i + 1]))         
                break ;
            i++;
        }
        response = ft_strjoin(response, ft_substr(node->value, x, i - x , addresses), addresses);
        if (((char *)node->value)[i] != '\0')
            i++;
        x = i;
        while(((char *)node->value)[i] != '\0' && ft_isalnum(((char *)node->value)[i]))
            i++;
        var = ft_substr(node->value, x, i - x, addresses);
        response = ft_strjoin(response, get_environment(env->env, var, addresses), addresses);
        x = i;
    }
    node->value = response;
    return ;
}

char	*expand_heredoc(char *var, char **env, t_node **add)
{
	int		i;
	char	*response;
	int		x;

	x = 0;
	i = 0;
	response = NULL;
	while (var && var[i])
	{
		while (var[i] != '\0')
		{
			if (var[i] == '$' && ft_isalnum(var[i + 1]))
				break ;
			i++;
		}
		response = ft_strjoin(response, ft_substr(var, x, i - x, add), add);
		if (var[i] != '\0')
			i++;
		x = i;
		while (var[i] != '\0' && ft_isalnum(var[i]))
			i++;
		var = ft_substr(var, x, i - x, add);
		response = ft_strjoin(response, get_environment(env, var, add), add);
		x = i;
	}
	return (response);
}