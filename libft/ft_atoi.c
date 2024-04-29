/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:31:32 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/29 21:09:26 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <limits.h>

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long		result;
	// long long		prev;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		if(result > LONG_MAX)
		{
			ft_putendl_fd("minishell: numeric argument required", 2);
			exit_status(255);
			return (255);
		}
		i++;
	}
	return (sign * result);
}
// int	ft_atoi(const char *str)
// {
// 	int			sign;
// 	long long	res;
// 	long long	prev;
// 	char		*s;
// 	char		*save;

// 	sign = 1;
// 	res = 0;
// 	save = (char *)str;
// 	while (*str != '\0' && (*str == ' ' || *str == '\n' || *str == '\t'
// 			||*str == '\f' || *str == '\r' || *str == '\v'))
// 		str++;
// 	s = ft_checksign(str, &sign);
// 	while (*s >= '0' && *s <= '9')
// 	{
// 		prev = res;
// 		res = res * 10 + (*s - 48);
// 		if (prev != res / 10)
// 			(ft_putstr_fd("exit\n", 2), print_error(3, "exit", save,
// 					"numeric argument required"), exit_with_status(255),
// 				exit(-1));
// 		s++;
// 	}
// 	return (sign * res);
// }