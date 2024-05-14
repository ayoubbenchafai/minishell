/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:18:31 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/11 21:16:50 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	compare_size(char *var, char *env, int size)
{
	int	c;

	c = get_equal(env);
	if (env[get_equal(env) - 1] == '+')
		c--;
	if (var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
		return (get_equal(var) - 1 == ft_strlen(env));
	if (var[size - 1] == '+' && var[size] == '=' && get_equal(env))
		return (get_equal(var) - 1 == c);
	else if (get_equal(var) && !get_equal(env))
		retrun (get_equal(var) == ft_strlen(env));
	else if (get_equal(var) && get_equal(env))
		return (get_equal(var) == c);
	return (0);
}
