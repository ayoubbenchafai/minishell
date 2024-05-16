/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:31:15 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/16 14:19:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_helper(char *path, t_env *env, char **tmp, t_node **addresses)
{
    char *all;
    char *cwd;

    cwd = getcwd(NULL, 0);
    *tmp = ft_strjoin(cwd, "/", addresses);
	if (!*tmp)
		return (free(cwd), -1);
    all = ft_strjoin(*tmp, path, addresses);
	if (!all)
		return (free(*tmp), free(cwd), -1);
    *tmp = all;
	return(chdir(all));
}

int exec_cd(char *path, t_env *env, t_node **addresses)
{
	int response;
	char *tmp;
    char **full_path;
    char *cwd;

    tmp = path;
	if(!path)
	{
		ft_putstr_fd("cd without any absolute or relative path \n", 2);
		return (0);
	}
	if(path[0] == '/')
		response = chdir(path);
	else
        response = cd_helper(path, env, &tmp, addresses);
	if (response == -1)
		return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(path, 2),
            ft_putstr_fd(": No such file or directory\n", 2), exit_status(1), 0);
	else
	{
		full_path = ft_array(NULL, ft_strjoin("OLDPWD=", get_environment(env->env, "PWD", addresses), addresses), addresses);
		exec_export(full_path, &env->env, &env->export, addresses);
		cwd = getcwd(NULL, 0);
		full_path = ft_array(NULL, ft_strjoin("PWD=", cwd, addresses), addresses);
		exec_export(full_path, &env->env, &env->export ,addresses);
		free(cwd);
	}
	return (1);
}
