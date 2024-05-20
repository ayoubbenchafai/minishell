/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 18:12:42 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	get_equal(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	get_dollar(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (0);
}
