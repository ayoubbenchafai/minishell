/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:18:31 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/14 14:22:12 by aben-cha         ###   ########.fr       */
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

int	handle_append_or_red_out(t_node **node, int *fd_out, int flag)
{
	if (!*node)
		return (1);
	if (!ft_strcmp((*node)->type, "append")
		|| !ft_strcmp((*node)->type, "rd_out"))
	{
		flag = 0;
		if (!ft_strcmp((*node)->type, "append"))
			flag = 1;
		*node = (*node)->next;
		while (*node && !ft_strcmp((*node)->type, "space"))
			*node = (*node)->next;
		if (!*node)
			return (error_redirection(0), 1);
		if (*node && (!ft_strcmp((*node)->type, "word")
				|| !ft_strcmp((*node)->type + 2, "quote")))
		{
			if (open_file(node, fd_out, flag))
				return (1);
		}
		else
			return (error_redirection(1), 1);
	}
	return (0);
}
