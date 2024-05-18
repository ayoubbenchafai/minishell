/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:28:32 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 18:56:54 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_redirection(int flag)
{
	if (flag == 0)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (flag == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (flag == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	exit_status(258);
	return ;
}

void	check_errors_child(char *cmd)
{
	if(cmd[0] == '.' && !cmd[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		exit(2);
	}
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else if (check_char(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (cmd[0] != '$')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	exit(127);
}

int	check_error(char *var, int flag)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (var[i] == '_')
	{
		if (!var[i + 1])
			return (1);
		i++;
	}
	if (i == 0 && !ft_isalpha(var[i]))
		return (0);
	j = i;
	if (!ft_isalnum(var[i]))
		return (0);
	size = get_equal(var);
	if (!case_one(var, &i, size))
		return (0);
	i += j;
	if (flag == 1)
		if (!case_two(var, i, size))
			return (0);
	return (1);
}
