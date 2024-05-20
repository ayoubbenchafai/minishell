/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:59:24 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/20 16:13:45 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_heredoc(char *var, char **env, t_node **add)
{
	int		i;
	char	*response;
	int		x;

	x = 0;
	i = 0;
	response = NULL;
	while (var && var[i])
	{
		i = process_value(var, i);
		response = ft_strjoin(response, ft_substr(var, x, i - x, add), add);
		if (var[i] != '\0')
			i++;
		x = i;
		while (var[i] != '\0' && ft_isalnum(var[i]))
			i++;
		var = ft_substr(var, x, i - x, add);
		response = ft_strjoin(response, get_environment(env, var, add), add);
		x = i;
	}
	return (response);
}

bool	valid_id(char *str, char c)
{
	int	i;

	i = 0;
	if (c)
	{
		if (str[i] == c && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			return (true);
	}
	else
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			return (true);
	}
	return (false);
}

void	t_word(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			break ;
		++i;
	}
	tmp = ft_malloc(i + 1, addresses);
	if (!tmp)
		return ;
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "word", addresses));
	*offset = *offset + i - 1;
}

void	replace_node(t_node *n, char *line, t_node **add)
{
	t_node	*tmp;
	t_node	*backup;
	int		i;

	tmp = NULL;
	i = 0;
	line = ft_strtrim(line, " ", add);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			ft_lstadd_back1(&tmp, ft_lstnew1(" ", "space", add));
		else
			t_word(&line[i], &tmp, &i, add);
		if (line[i])
			i++;
	}
	backup = n->next;
	n->value = tmp->value;
	n->type = tmp->type;
	n->next = tmp->next;
	ft_lstadd_back1(&n, backup);
}

void	expand(t_node *n, t_env *env, t_node **add, char *res)
{
	int		i;
	int		x;
	char	*s;

	i = 0;
	x = 0;
	if (!n || !ft_strcmp(n->type, "s_quote"))
		return ;
	while (n->value && ((char *)n->value)[i])
	{
		i = process_value(n->value, i);
		res = ft_strjoin(res, ft_substr(n->value, x, i - x, add), add);
		if (((char *)n->value)[i] != '\0')
			i++;
		x = i;
		while (((char *)n->value)[i] && valid_id(&((char *)n->value)[i], 0))
			i++;
		s = get_environment(env->env, ft_substr(n->value, x, i - x, add), add);
		res = ft_strjoin(res, s, add);
		x = i;
	}
	if (ft_strcmp(res, n->value) > 0)
		replace_node(n, res, add);
	else
		n->value = ft_strtrim(res, " ", add);
}
