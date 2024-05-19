/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:07:13 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 18:21:10 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_size(char *var, char *env, int size)
{
	int	c;

	c = get_equal(env);
	if (c && env[c - 1] == '+')
		c--;
	if (size && var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
		return (get_equal(var) - 1 == ft_strlen(env));
	else if (size && var[size - 1] == '+' && var[size] == '=' && get_equal(env))
		return (get_equal(var) - 1 == c);
	else if (get_equal(var) && !get_equal(env))
		return (get_equal(var) == ft_strlen(env));
	else if (get_equal(var) && get_equal(env))
		return (get_equal(var) == c);
	return (0);
}

int	check_if_var_exist(char *var, char *env, int size)
{
	if (!ft_strncmp(env, var, size) && cmp_size(env, var))
		return (1);
	return (0);
}

int	get_best_size(char *var)
{
	int	j;
	int	size;

	j = 0;
	size = get_equal(var);
	if (size == 0)
		j = ft_strlen(var);
	else
	{
		if (var[size - 1] == '+' && var[size] == '=')
			j = size - 1;
		else
			j = size;
	}
	return (j);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	check_char(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
