/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:31:15 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/09 16:16:36 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int exec_cd(char *path, t_env *env, t_node **addresses)
// {
// 	int response;
// 	char *tmp;
// 	if(!path)
// 	{
// 		ft_putstr_fd("cd without any absolute or relative path \n", 2);
// 		return (0);
// 	}
// 	if(path[0] == '/')
// 	{
// 		response = chdir(path);
// 		tmp = path;
// 	}
// 	else
// 	{
// 		tmp = ft_strjoin(get_environment(env->env, "PWD="), "/", addresses);
// 		if (!tmp)
// 			return (0);
// 		tmp = ft_strjoin(tmp, path, addresses);
// 		if (!tmp)
// 			return (0);
// 		response = chdir(tmp);
// 	}
// 	if(response == -1)
// 	{
// 		ft_putstr_fd("cd: ", 2);
// 		ft_putstr_fd(path, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		return (1);
// 	}
// 	else
// 	{
// 		char *cwd = getcwd(NULL, 0);
// 		exec_export(ft_strjoin("OLDPWD=", get_environment(env->env, "PWD"), addresses), &env->env, &env->export ,addresses);
// 		exec_export(ft_strjoin("PWD=", getcwd(NULL, 0), addresses),&env->env, &env->export, addresses);
// 		free(cwd);
// 	}
// 	return (1);
// }
