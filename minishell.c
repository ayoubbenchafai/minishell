/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:09:21 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/18 16:40:35 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *commands, t_env *env, t_node **addresses)
{
	if (!commands->cmd)
		return (0);
	if (!ft_strcmp(commands->cmd[0], "echo"))
		return (exec_echo(commands->cmd, env->env, addresses), 1);
	else if (!ft_strcmp(commands->cmd[0], "pwd"))
		return (exec_pwd(), 1);
	else if (!ft_strcmp(commands->cmd[0], "cd"))
		return (exec_cd(commands->cmd[1], env, addresses), 1);
	else if (!ft_strcmp(commands->cmd[0], "env"))
		return (exec_env(env->env), 1);
	else if (!ft_strcmp(commands->cmd[0], "export"))
		return (exec_export(&commands->cmd[1], &env->env, &env->export), 1);
	else if (!ft_strcmp(commands->cmd[0], "unset"))
		return (exec_unset(&commands->cmd[1], env), 1);
	else if (!ft_strcmp(commands->cmd[0], "exit"))
		return (exec_exit(commands->cmd), 1);
	return (0);
}

int	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return (1);
}

void	backup_dup(void)
{
	static int	fd;
	static int	i;

	if (i == 0)
	{
		fd = dup(0);
		i++;
	}
	else
		dup2(fd, 0);
}

void	init(t_node **addresses, t_env *envir, t_node **tokens, char **env)
{
	*addresses = NULL;
	*tokens = NULL;
	if (envir)
	{
		envir->env = get_env(env);
		envir->export = get_env(env);
	}
	backup_dup();
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_node			*tokens;
	t_node			*add;
	t_env			env;
	struct termios	original_termios;

	init(&add, &env, &tokens, envp);
	get_terminal_attr(&original_termios);
	while (1)
	{
		run_signals(1);
		line = readline("minishell$ ");
		if (!line && free_arr(env.env) && free_arr(env.export))
			return (rl_clear_history(), close(3), ctr_d(), 0);
		if (quotes_syntax(line))
			continue ;
		if (line[0] != '\0' && ((line[0] < 9 || line[0] > 13) && line[0] != 32))
			add_history(line);
		parse_line(line, &tokens, &add, 0);
		loop_process(set_newlist(&tokens, &env, &add), &env, &add);
		restore_terminal_attributes(&original_termios);
		(free(line), free_addresses(add));
		init(&add, NULL, &tokens, NULL);
	}
	return (0);
}
