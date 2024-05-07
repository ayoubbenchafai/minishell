/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:48:57 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/06 21:37:10 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy(char *ptr, const char *s)
{
	while (*ptr)
		ptr++;
	while (*s)
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2, t_node **addresses)
{
	size_t	len;
	char	*ptr;

	if (!s1 && !s2)
		return (ft_strdup("", addresses));
	if (!s1)
		return (ft_strdup(s2, addresses));
	if (!s2)
		return (ft_strdup(s1, addresses));
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_malloc(len + 1, addresses);
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	copy(ptr, s1);
	copy(ptr, s2);
	return (ptr);
}
