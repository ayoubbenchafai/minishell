/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:31:32 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/27 14:55:30 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <limits.h>

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long	result;

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
		// if(result == LONG_MAX && sign == 1)
		// {
		// 	printf("result = %lld\n", result);
		// 	return (255);
		// }
		// else if ((result > LONG_MAX) && (sign == 1))
		// {
		// 	ft_putendl_fd("minishell: numeric argument required", 2);
		// 	exit_status(255);
		// 	return (255);
		// }
		// else if ((result > LONG_MAX) && (sign == -1))
		// {
		// 	ft_putendl_fd("minishell: numeric argument required", 2);
		// 	exit_status(255);
		// 	return (255);
		// }
		i++;
	}
	// printf("result = %lld\n", result);
	return (sign * (int)result);
}

// int	ft_atoi(const char *str)
// {
//     int				i;
//     int				sign;
//     long long	result;

//     i = 0;
//     sign = 1;
//     result = 0;
//     while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
//         i++;
//     if (str[i] == '-' || str[i] == '+')
//     {
//         if (str[i] == '-')
//             sign *= -1;
//         i++;
//     }
//     while (str[i] >= '0' && str[i] <= '9')
//     {
//         result = (result * 10) + str[i] - '0';
//         if(result > LONG_MAX)
//         {
//             ft_putendl_fd("minishell: numeric argument required", 2);
//             exit_status(255);
//             return (255);
//         }
//         i++;
//     }
//     result = sign * result;
//     if(result < 0)
//     {
//         result = 256 + result;
//     }
//     return (result % 256);
// }