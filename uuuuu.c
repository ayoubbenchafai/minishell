/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uuuuu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:22:16 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/15 16:23:48 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



static void	print_error(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}



