/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:24:09 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/19 18:56:05 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env)
{
	int		i;
	char	**array;

	i = 0;
	while (env[i])
		i++;
	array = malloc((sizeof(char *) * (i + 1)));
	if (!array)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		array[i] = malloc((sizeof(char) * (ft_strlen(env[i]) + 1)));
		if (!array[i])
			return (NULL);
		ft_strlcpy(array[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	get_equal(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_char(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
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

int	process_value(char *value, int i)
{
	while (value[i] != '\0')
	{
		if (valid_id(&value[i], '$'))
			break ;
		i++;
	}
	return (i);
}

void	expand(t_node *n, t_env *env, t_node **add, char *res)
{
	int		i;
	int		x;
	char	*s;

	res = NULL;
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
		replace_node(n, res, res, add);
	else
		n->value = ft_strtrim(res, " ", add);
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

void	replace_node(t_node *n, char *line, char *res, t_node **add)
{
	t_node	*tmp;
	t_node	*backup;
	int i = 0;
	tmp = NULL;

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
