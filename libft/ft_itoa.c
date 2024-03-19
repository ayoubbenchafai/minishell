/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:24:52 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/06 19:19:19 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_counter(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i = 1;
	while (nbr)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char		*ptr;
	long int	nbr_long;
	int			size;

	size = size_counter(nbr);
	ptr = (char *)malloc(size + 1);
	if (ptr == NULL)
		return (ptr);
	ptr[size] = '\0';
	if (nbr == 0)
		ptr[0] = 48;
	nbr_long = (long int)nbr;
	if (nbr_long < 0)
	{
		ptr[0] = '-';
		nbr_long = -nbr_long;
	}
	while (nbr_long)
	{
		ptr[size - 1] = nbr_long % 10 + 48;
		nbr_long = nbr_long / 10;
		size--;
	}
	return (ptr);
}
