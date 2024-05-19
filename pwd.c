/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:18:13 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 15:19:17 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: ", 1);
		ft_putstr_fd("\n", 1);
		exit_status(1);
		return (0);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	exit_status(0);
	free(pwd);
	return (1);
}
