/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:53:05 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/03 15:51:26 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	check_char(const char *set, char c)
// {

// 	while (set && *set)
// 	{
// 		if (*set == c)
// 			return (1);
// 		set++;
// 	}
// 	return (0);
// }

char	*ft_strtrim(char *s1, char *set, t_node **addresses)
{
	int	begin;
	int	end;
	int	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (s1[begin] && check_char(set, s1[begin]))
		begin++;
	while ((end >= 0) && check_char(set, s1[end]))
		end--;
	size = end - begin + 1;
	return (ft_substr(s1, begin, size, addresses));
}
