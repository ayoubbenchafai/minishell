/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 19:05:16 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/20 16:12:19 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_cmd(t_command *cmd)
{
	int			len;
	t_command	*ptr;

	if (!cmd)
		return (0);
	len = 0;
	ptr = cmd;
	while (ptr)
	{
		len++;
		ptr = ptr -> next;
	}
	return (len);
}

char	*ft_join_free(char *s, const char *buf, t_node **addresses)
{
	char	*r;

	r = ft_strjoin(s, buf, addresses);
	return (r);
}

char	**ft_ft_array(char **array, char *s)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!array)
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = s;
		new[1] = NULL;
		return (new);
	}
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	while (array[++j])
		new[j] = array[j];
	new[j] = ft_ft_strdup(s);
	new[j + 1] = NULL;
	return (free(array), new);
}

char	*request_env(char **envp, char *var)
{
	int		i;
	char	*response;

	response = NULL;
	i = 0;
	while (envp && envp[i])
	{
		response = ft_strnstr(envp[i], var, ft_strlen(var));
		if (response)
			return (response + ft_strlen(var));
		i++;
	}
	return (NULL);
}

char	*get_environment(char **envp, char *var, t_node **addresses)
{
	char	*tmp;
	char	*response;

	tmp = NULL;
	response = NULL;
	tmp = ft_strjoin(var, "=", addresses);
	if (!tmp)
		return (NULL);
	response = request_env(envp, tmp);
	if (!response)
	{
		tmp = ft_strjoin(var, "+=", addresses);
		response = request_env(envp, tmp);
	}
	return (response);
}
