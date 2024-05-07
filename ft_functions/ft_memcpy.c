/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:16:17 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/07 16:27:10 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*ptr;

	if (!dst && !src)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)dst;
	while (i < len)
	{
		*ptr = *((unsigned char *)src);
		i++;
		src++;
		ptr++;
	}
	return (dst);
}
