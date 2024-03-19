/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:16:13 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/03 19:24:04 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t nbr)
{
	void	*ptr;

	if ((int)count == -1 && (int)nbr == -1)
		return (NULL);
	ptr = (char *)malloc(count * nbr);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * nbr));
	return (ptr);
}
