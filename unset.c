/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:16:02 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/13 15:56:55 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_size(char *env, char *var)
{
	int	c;

	c = get_equal(env);
	if ((c && (c - 1 == ft_strlen(var) && env[c - 1] == '+')
			|| c == ft_strlen(var) || !ft_strcmp(env, var)))
		return (1);
	return (0);
}

int	get_len_env(char **env, char *var, int size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env && env[i])
	{
		if (!(!ft_strncmp(env[i], var, size) && cmp_size(env[i], var)))
			len++;
		i++;
	}
	return (len);
}

void	exec_unset(char *var, char ***env, t_node **addr)
{
	int		size;
	int		i;
	int		len;
	char	**unset;
	int		j;

	if (!var)
		return ;
	size = ft_strlen(var);
	len = get_len_env(*env, var, size);
	unset = ft_malloc(sizeof(char *) * (len + 1), addr);
	if (!unset)
		return ;
	i = 0;
	j = 0;
	while (env && *env && (*env)[i])
	{
		if (!(!ft_strncmp((*env)[i], var, size) && cmp_size((*env)[i], var)))
			unset[j++] = ft_strdup((*env)[i], addr);
		i++;
	}
	unset[j] = NULL;
	*env = unset;
	exit_status(0);
}
