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
	char *special = " <>&|;\'\"\t";
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
	tmp = ft_malloc(i + 1, addresses);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "var", addresses));
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
	tmp = ft_malloc(i + 1, addresses);
	if(!tmp)
		return ;
	while(j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "word", addresses));
	// free(tmp);
	*offset = *offset + i - 1;
}
void ft_quotes(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int i;
	int j;
	char *tmp;

	i = 1;
	j = 0;
	while(line[i])
	{
		if(line[0] == line[i])
			break;
		++i;
	}
	tmp = ft_malloc(i + 1, addresses);
	if(!tmp)
		return ;
	while(j < i-1)
	{
		tmp[j] = line[j+1];
		j++;
	}
	tmp[j] = '\0';
	if (line[0] == '\'')
		ft_lstadd_back1(commands, ft_lstnew1(tmp, "s_quote", addresses));
	else
		ft_lstadd_back1(commands, ft_lstnew1(tmp, "d_quote", addresses));
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
		// else if(line[i] == '$')
		// 	ft_expand(&line[i], commands, &i, addresses);
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

int quotes_syntax(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '\'' && check_quote(&line[i], '\'', &i) == 0)
		{
			printf("quote error\n");
			exit_status(127);
			return 1;
		}
		if(line[i] == '\"' && check_quote(&line[i], '\"', &i) == 0)
		{
			printf("quote error\n");
			exit_status(127);
			return 1;
		}
		if(line[i])
			i++;
	}
	return 0;
}
int is_builtin(t_command *commands, t_env *env, t_node **addresses)
{
	if (!commands->cmd)
		return (0);
	if(!ft_strcmp(commands->cmd[0], "echo"))
		return(exec_echo(commands->cmd, env->env, addresses), 1);
	else if(!ft_strcmp(commands->cmd[0], "pwd"))
		return (exec_pwd(), 1);
	else if(!ft_strcmp(commands->cmd[0], "cd"))
		return (exec_cd(commands->cmd[1], env, addresses), 1);      
	else if(!ft_strcmp(commands->cmd[0], "env"))
		return (exec_env(env->env), 1);
	else if(!ft_strcmp(commands->cmd[0], "export"))
		return (exec_export(&commands->cmd[1], &env->env, &env->export), 1);
	else if(!ft_strcmp(commands->cmd[0], "unset"))
		return (exec_unset(&commands->cmd[1], env), 1);
	else if(!ft_strcmp(commands->cmd[0], "exit"))
		return (exec_exit(commands->cmd), 1);
	return (0);
}

void f(void)
{
	sleep(5);
}
void free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char    *line;
	t_node  *tokens;
    t_node  *addresses;
	t_env   envir;
	struct termios original_termios;
	// atexit(f);
	line = NULL;
	tokens = NULL;
	addresses = NULL;
	envir.env = get_env(env);
	envir.export = get_env(env);
	get_terminal_attr(&original_termios);
	int backup = dup(0);
	while (1)
	{
		run_signals(1);
		line = readline("minishell$ ");
		if(!line)
				return (free(line),	free_arr(envir.env), free_arr(envir.export), rl_clear_history(), close(backup), ctr_d(), 0);
		if(quotes_syntax(line))
		{
			free(line);
			line = NULL;
			continue;
		}
		if (line[0] != '\0' && ((line[0] < 9 || line[0] > 13) && line[0] != 32))
			add_history(line);
		parse_line(line, &tokens, &addresses, 0);
		loop_process(set_newlist(&tokens, &envir, &addresses), &envir, &addresses);
		dup2(backup, 0);
		tokens = NULL;
		free(line);
		line = NULL;
		restore_terminal_attributes(&original_termios);
		// free_addresses(addresses);
		// addresses = NULL;
    }
	// ft_minishell(tokens, envir, addresses, &original_termios);
	return 0;
}


