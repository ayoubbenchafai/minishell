#include "minishell.h"

int check_pipes(char *line)
{
	int i;
	int flag;
	i = 0;
	flag = 0;
	while(line[i])
	{
		if(line[i] == '|')
			flag = 1;
		i++;
	}
	return flag;
}

int special_char(char c)
{
	char *special = " $<>&|;\'\"\t";
	int i = 0;
	while(special[i])
	{
		if(special[i] == c)
			return 1;
		i++;
	}
	return 0;
}
void ft_expand(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	++i;
	while(line[i])
	{
		if(special_char(line[i]))
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "var", addresses));
	free(tmp);
	*offset = *offset + i - 1;
}

void ft_word(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	while(line[i])
	{
		if(special_char(line[i]))
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "word", addresses));
	free(tmp);
	*offset = *offset + i - 1;
}
void ft_quotes(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;
	tmp = NULL;
	i = 0;
	j = 0;
	++i;
	while(line[i])
	{
		if(line[0] == line[i])
			break;
		++i;
	}
	tmp = malloc(i + 1);
	if(!tmp)
		return ;
	while(j < i-1)
	{
		tmp[j] = line[j+1];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "quote", addresses));
	free(tmp);
	*offset = *offset + i;
}
int check_quote(char *line, char c,	int *offset)
{
	int i;
	int j;
	int last;
	i = 0;
	j = 0;

	while(line[i])
	{
		if(line[i] == c)
		{
			last = i;
			j++;
		}
		i++;
	}
	if(j % 2 == 0)
	{
		if (offset)
			*offset += last;
		return 1;
	}
	return 0;
}

void parse_line(char *line, t_node **commands, t_node **addresses, int i)
{
	while(line[i])
	{
		if(line[i] == ' ' || line[i] == '\t')
			ft_lstadd_back1(commands, ft_lstnew1(" ", "space", addresses));
		else if(line[i] == '$')
			ft_expand(&line[i], commands, &i, addresses);
		else if(line[i] == '<' && line[i + 1] == '<' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1("<<", "here_doc", addresses));
		else if(line[i] == '>' && line[i + 1] == '>' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1(">>", "append", addresses));
		else if(line[i] == '<')
			ft_lstadd_back1(commands, ft_lstnew1("<", "rd_in", addresses));
		else if(line[i] == '>')
			ft_lstadd_back1(commands, ft_lstnew1(">", "rd_out", addresses));
		else if(line[i] == '|')
			ft_lstadd_back1(commands, ft_lstnew1("|", "pipe", addresses));
		else if(line[i] == '\'' && check_quote(&line[i], '\'', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else if(line[i] == '\"' && check_quote(&line[i], '\"', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else
			ft_word(&line[i], commands, &i, addresses);
		if(line[i])
			i++;
	}
}
void f()
{
	system("leaks minishell");
}
int quotes_syntax(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '\'' && check_quote(&line[i], '\'', &i) == 0)
		{
			printf("quote error\n");
			return 1;
		}
		if(line[i] == '\"' && check_quote(&line[i], '\"', &i) == 0)
		{
			printf("quote error\n");
			return 1;
		}
		if(line[i])
			i++;
	}
	return 0;
}
int is_builtin(t_command *commands, char ***env, char ***export_env, t_node **addresses)
{
	if(!commands->cmd)
		return 0;
	if(!ft_strncmp(commands->cmd[0], "echo", 4))
		return(exec_echo(commands->cmd, *env), 1);
	else if(!ft_strncmp(commands->cmd[0], "pwd", 3))
		return (exec_pwd(), 1);
	else if(!ft_strncmp(commands->cmd[0], "cd", 2))
		return (exec_cd(commands->cmd[1]), 1);
	else if(!ft_strncmp(commands->cmd[0], "env", 3))
		return (exec_env(*env), 1);
	// if(!ft_strncmp(commands->cmd[0], "export", 6) && commands->cmd[1])
	if(!ft_strncmp(commands->cmd[0], "export", 6))
		return (exec_export(commands->cmd[1], env, export_env), 1);
	else if(!ft_strncmp(commands->cmd[0], "unset", 5))
		return (exec_unset(commands->cmd[1], env),1);
	else if(!ft_strncmp(commands->cmd[0], "$", 1))
		return (printf("command not found: "), expand(commands->cmd[0], *env), 1);
	return 0;
}
void exec_echo(char **cmd, char **env)
{
	if(!ft_strncmp(cmd[1], "-n", 2))
	{
		int i;
		i = 1;
		while(cmd[i++])
		{
			if(!expand(cmd[i], env))
				ft_putstr_fd(cmd[i], 1);
			if(cmd[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	else
	{
		int i;

		i = 0;
		if(!cmd[1])
		{
			ft_putstr_fd("\n", 1);
			return ;
		}
		while(cmd[i++])
		{
			if(!expand(cmd[i], env))
				ft_putstr_fd(cmd[i], 1);
			if(cmd[i + 1])
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
}
int main(int argc, char **argv, char **env)
{
	char    *line = NULL;
	t_node  *tokens = NULL;
    t_node  *addresses = NULL;
	char **env_lst = get_env(env);
	char **export_env = get_env(env);
	get_exit_status = 0;
	run_signals();
	while(1)
	{
		line = readline("minishell$ ");
		if(!line || !strncmp(line, "exit", 4))
			return (free(line),	free_addresses(addresses), rl_clear_history(), ctr_d(),0);
		if(line[0] != '\0')
			add_history(line);
		if(quotes_syntax(line))
		{
			free(line);
			continue;
		}
		parse_line(line, &tokens, &addresses, 0);
		execute_commands(set_newlist(&tokens), &env_lst, &export_env ,&addresses);
		tokens = NULL;
		free(line);
    }
	free_addresses(addresses);
	return 0;
}
