/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:19:25 by aben-cha          #+#    #+#             */
/*   Updated: 2023/11/10 11:46:42 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int				len;
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	len = n - 1;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (len >= 0 && d > s)
	{
		d[len] = s[len];
		len--;
	}
	while (i < n && d < s)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
