/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:19:19 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/06 21:48:25 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (!n)
		return (0);
	if(!s1 && s2)
		return (-s2[0]);
	if(!s2 && s1)
		return (s1[0]);
	if (!s1 && !s2)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] && i < n)
		return (s1[i]);
	else if (s2[i] && i < n)
		return (-s2[i]);
	return (0);
}
/*int main ()
{
	printf("%d", ft_strncmp("", "1", 1));
	return (0);
}
*/
