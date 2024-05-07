/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:28:20 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/06 21:32:54 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str, t_node **addresses)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(str);
	ptr = ft_malloc(len + 1, addresses);
	if (ptr == NULL)
		return (NULL);
	ptr = (char *)ft_memcpy(ptr, str, len);
	ptr[len] = '\0';
	return (ptr);
}
