/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/15 16:13:09 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

int	case_one(char *var, int *i, int size)
{
	while (var && var[*i] && !size)
	{
		if (var[*i] != '_')
			if (!ft_isalnum(var[*i]))
				return (0);
		(*i)++;
	}
	return (1);
}

int	case_two(char *var, int i, int size)
{
	while (i < size)
	{
		if (var[i] != '_')
		{
			if (var[i] == '+' && var[i + 1])
			{
				i++;
				if (var[i] == '=')
					break ;
				else
					return (0);
			}
			if (!ft_isalnum(var[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_error(char *var, int flag)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (var[i] == '_')
	{
		if (!var[i + 1])
			return (1);
		i++;
	}
	if (i == 0 && !ft_isalpha(var[i]))
		return (0);
	j = i;
	if (!ft_isalnum(var[i]))
		return (0);
	size = get_equal(var);
	if (!case_one(var, &i, size))
		return (0);
	i += j;
	if (flag == 1)
		if (!case_two(var, i, size))
			return (0);
	return (1);
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
