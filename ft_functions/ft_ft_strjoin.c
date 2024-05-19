/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:13 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/16 17:09:09 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_copy(char *ptr, const char *s)
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

char	*ft_ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*ptr;

	if (!s1 && !s2)
		return (ft_ft_strdup(""));
	if (!s1)
		return (ft_ft_strdup(s2));
	if (!s2)
		return (ft_ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	ft_copy(ptr, s1);
	ft_copy(ptr, s2);
	return (ptr);
}