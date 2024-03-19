/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:10:35 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/07 15:53:41 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	start;

	start = ft_strlen(str);
	while (start >= 0)
	{
		if (str[start] == (unsigned char)c)
			return ((char *)&str[start]);
		start--;
	}
	return (NULL);
}
