/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:39:58 by aben-cha          #+#    #+#             */
/*   Updated: 2023/11/16 15:51:10 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	d;

	i = 0;
	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	len_dest = ft_strlen(dest);
	d = len_dest;
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	while (src[i] && (d < dstsize - 1))
	{
		dest[d++] = src[i];
		i++;
	}
	dest[d] = '\0';
	return (len_dest + len_src);
}
