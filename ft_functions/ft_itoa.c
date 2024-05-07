/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:42:47 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/03 18:14:08 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	number_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_node **addresses)
{
	int		size;
	char	*ptr;

	size = number_digits(n);
	ptr = ft_malloc(size + 1, addresses);
	if (!ptr)
		return (NULL);
	ptr[size] = '\0';
	if (n < 0)
		ptr[0] = '-';
	if (n == 0)
		ptr[0] = '0';
	size--;
	while (n != 0)
	{
		ptr[size--] = n % 10 * ((n >= 0) - (n < 0)) + '0';
		n /= 10;
	}
	return (ptr);
}
