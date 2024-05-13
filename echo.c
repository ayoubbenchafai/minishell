/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:42:21 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/10 15:45:18 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_status(char *cmd, int flag, t_node **addresses)
{
	int	i;

	i = 0;
	if (flag)
		ft_putstr_fd("minishell: ", 1);
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
		{
			ft_putstr_fd(ft_itoa(exit_status(-1), addresses), 1);
			i += 1;
		}
		else
			ft_putchar_fd(cmd[i], 1);
		i++;
	}
	if (flag)
		ft_putstr_fd(": command not found\n", 1);
}

static void	print_words(char **words, int flag, t_node **addresses)
{
	int	i;

	i = 0;
	while (words && words[i])
	{
		print_exit_status(words[i], 0, addresses);
		if (words[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	exit_status(0);
}

void	exec_echo(char **cmd, char **env, t_node **addresses)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd && cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			j = 0;
			while (cmd[i][++j] == 'n')
				;
			if (cmd[i][j] != '\0')
				break ;
			else
				flag = 1;
		}
		else
			break ;
	}
	print_words(&cmd[i], flag, addresses);
}
