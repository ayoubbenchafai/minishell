/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:26:19 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/06 21:58:35 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char str, char const *set)
{
	while (*set)
	{
		if (*set == str)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *str, char *set, t_node **addresses)
{
	int	i;
	int	start;

	i = 0;
	if (!str || !*str)
		return (str);
	while (check(str[i], set))
		i++;
	if (str[i])
		start = i;
	while (str[i])
		i++;
	while (check(str[i - 1], set))
		i--;
	return (ft_substr(str, start, i - start, addresses));
}
