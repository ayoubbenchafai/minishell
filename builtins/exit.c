/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:23 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/20 16:13:39 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, int flag)
{
	if (!flag)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("':not a valid identifier\n", 2);
		exit_status(1);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_status(255);
		exit(255);
	}
}

static void	check_error_exit(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '-')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			print_error(str, 1);
		i++;
	}
}

void	exec_exit(char **cmd)
{
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit_status(0);
		exit(0);
	}
	else if (cmd && cmd[1] && cmd[2])
	{
		check_error_exit(cmd[1]);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_status(1);
		return ;
	}
	else
		check_error_exit(cmd[1]);
	if (cmd && cmd[1])
	{
		exit_status(ft_atoi(cmd[1]));
		exit(ft_atoi(cmd[1]));
	}
}
