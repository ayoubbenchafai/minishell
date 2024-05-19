/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/19 19:08:56 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env)
{
	int		i;
	char	**array;

	i = 0;
	while (env[i])
		i++;
	array = malloc((sizeof(char *) * (i + 1)));
	if (!array)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		array[i] = malloc((sizeof(char) * (ft_strlen(env[i]) + 1)));
		if (!array[i])
			return (NULL);
		ft_strlcpy(array[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	exec_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '+' && env[i][j + 1] == '=')
				j++;
			write(1, &env[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}




