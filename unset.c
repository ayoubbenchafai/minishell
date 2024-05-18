/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:16:02 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/18 15:31:31 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_size(char *env, char *var)
{
	int	c;

	c = get_equal(env);
	if ((c && (c - 1 == ft_strlen(var) && env[c - 1] == '+')
			|| c == ft_strlen(var) || !ft_strcmp(env, var)))
		return (1);
	return (0);
}

int	get_len_env(char **env, char *var, int size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env && env[i])
	{
		if (!(!ft_strncmp(env[i], var, size) && cmp_size(env[i], var)))
			len++;
		i++;
	}
	return (len);
}

void	get_new_env(char **unset, char ***env, char *var, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env && *env && (*env)[i])
	{
		if (!(!ft_strncmp((*env)[i], var, size) && cmp_size((*env)[i], var)))
			unset[j++] = ft_ft_strdup((*env)[i]);
		if (!unset[j - 1])
		{
			free_arr(unset);
			return ;
		}
		i++;
	}
	free_arr(*env);
	unset[j] = NULL;
	*env = unset;
	exit_status(0);
}

void	ft_unset(char *var, char ***env)
{
	int		size;
	int		len;
	char	**unset;

	if (!var)
		return ;
	size = ft_strlen(var);
	len = get_len_env(*env, var, size);
	unset = malloc(sizeof(char *) * (len + 1));
	if (!unset)
		return ;
	get_new_env(unset, env, var, size);
}

void	exec_unset(char **vars, t_env *env)
{
	int	i;

	i = 0;
	while (vars && vars[i])
	{
		if (!check_error(vars[i], 0) || vars[i][get_equal(vars[i])] == '=')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(vars[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(1);
			i++;
			continue ;
		}
		ft_unset(vars[i], &env->env);
		ft_unset(vars[i], &env->export);
		i++;
	}
}
