/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:09:55 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/10 23:47:02 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	if (!haystack && !len)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	else if (ft_strlen(haystack) < ft_strlen(needle))
		return (NULL);
	while (*haystack && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len && needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	printf("%s\n",strnstr("gdggew","e",0));
// 	printf("%s",ft_strnstr("gdggew","e",0));
// }