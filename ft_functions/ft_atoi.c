/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:31:32 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/03 18:45:12 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char *str)
{
	ft_putendl_fd("exit", 2);
	printf("minishell: exit: %s: numeric argument required\n", str);
	exit(-1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	prev;

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
		prev = result;
		result = (result * 10) + str[i] - '0';
		if (prev != result / 10)
			print_error((char *)str);
		i++;
	}
	return (sign * result);
}
