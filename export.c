/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:12:58 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/13 13:23:51 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				swap (&env[i], &env[j]);
			j++;
		}
		i++;
	}
}

void	export_print(char **export_env)
{
	int	i;

	sort_env(export_env);
	while (export_env && *export_env)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while ((*export_env)[i])
		{
			if ((*export_env)[i] == '+' && (*export_env)[i + 1] == '=')
				i++;
			ft_putchar_fd((*export_env)[i], 1);
			if ((*export_env)[i] == '=' && (*export_env)[i - 1] != '=')
			// if ((*export_env)[i] == '=' && (*export_env)[i - 1] != '=' && (*export_env)[i + 1] != '=') if +
				ft_putchar_fd('"', 1);
			i++;
		}
		// if (check_char(*export_env, '+') && !get_equal(*export_env))
			// ft_putstr_fd("=\"", 1);
		if (get_equal(*export_env))
			ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		export_env++;
	}
	exit_status(0);
}

void	export_join(int flag, char *var, char **env, t_node **addresses)
{
	char	*s;

	if (!flag)
		s = ft_strjoin(*env, var + get_equal(var) + 1, addresses);
	else
		s = ft_strjoin(*env, var + get_equal(var), addresses);
	*env = ft_strdup(s, addresses);
}

int	compare_size(char *var, char *env, int size)
{
	int	c;

	c = get_equal(env);
	if (c && env[c - 1] == '+')
		c--;
	if (size && var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
		return (get_equal(var) - 1 == ft_strlen(env));
	else if (size && var[size - 1] == '+' && var[size] == '=' && get_equal(env))
		return (get_equal(var) - 1 == c);
	else if (get_equal(var) && !get_equal(env))
		return (get_equal(var) == ft_strlen(env));
	else if (get_equal(var) && get_equal(env))
		return (get_equal(var) == c);
	return (0);
}

void	env_export_all_cases(char *var, char ***env, int size, t_node **addr)
{
	int	i;
	int	len;
	int	flag;

	i = -1;
	flag = 0;
	len = get_equal(var);
	while (env && *env && (*env)[++i])
	{
		if (!ft_strncmp((*env)[i], var, size) && !len)
		{
			// printf("env : %s, var : %s\n", (*env)[i], var);
			// printf("env : (%d, - 1 %d) var : %zd\n", get_equal((*env)[i]), get_equal((*env)[i]) - 1, ft_strlen(var));
			int c = get_equal((*env)[i]);
			if ((c - 1 == ft_strlen(var) && (*env)[i][c - 1] == '+')
			|| c  == ft_strlen(var))
				return ;
			if (!ft_strcmp((*env)[i], var))
				return ;
		}
		else if (!ft_strncmp((*env)[i], var, size) && len)
		// else if (!ft_strncmp((*env)[i], var, size) && check_char(var, '='))
		{
			if (!check_char((*env)[i], '='))
				flag = 1;
			if (compare_size(var, (*env)[i], len))
			{
				if (var[len - 1] == '+' && var[len] == '=')
					export_join(flag, var, &(*env)[i], addr);
				else
					(*env)[i] = ft_strdup(var, addr);
				return ;
			}
		}
	}
	*env = ft_array(*env, var, addr);
}

void	exec_export(char **vars, char ***env, char ***ex_env, t_node **addr)
{
	int	i;
	int	size;

	i = 1;
	if (!vars || !*vars || !vars[1])
	{
		export_print(*ex_env);
		return ;
	}
	while (vars && vars[i])
	{
		size = get_best_size(vars[i]);
		if (!check_error(vars[i], 1))
		{
			printf("export: `%s':not a valid identifier\n", vars[i++]);
			continue ;
			exit_status(1);
		}
		if (!get_equal(vars[i]))
		{
			env_export_all_cases(vars[i++], ex_env, size, addr);
			continue ;
		}
		env_export_all_cases(vars[i], ex_env, size, addr);
		env_export_all_cases(vars[i++], env, size, addr);
	}
}
