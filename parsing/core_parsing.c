/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:28:23 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/20 16:12:44 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(char *line, t_node **commands, int *offset, t_node **add)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	++i;
	while (line[i])
	{
		if (special_char(line[i]))
			break ;
		++i;
	}
	tmp = ft_malloc(i + 1, add);
	if (!tmp)
		return ;
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
	ft_lstadd_back1(commands, ft_lstnew1(tmp, "var", add));
	*offset = *offset + i - 1;
}

void	ft_word(char *line, t_node **commands, int *offset, t_node **addresses)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (special_char(line[i]))
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

void	ft_quotes(char *line, t_node **commands, int *offset, t_node **add)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[++i])
	{
		if (line[0] == line[i])
			break ;
	}
	tmp = ft_malloc(i + 1, add);
	if (!tmp)
		return ;
	while (j < i - 1)
	{
		tmp[j] = line[j + 1];
		j++;
	}
	tmp[j] = '\0';
	if (line[0] == '\'')
		ft_lstadd_back1(commands, ft_lstnew1(tmp, "s_quote", add));
	else
		ft_lstadd_back1(commands, ft_lstnew1(tmp, "d_quote", add));
	*offset = *offset + i;
}

void	parse_line(char *line, t_node **commands, t_node **addresses, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			ft_lstadd_back1(commands, ft_lstnew1(" ", "space", addresses));
		else if (line[i] == '<' && line[i + 1] == '<' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1("<<", "here_doc", addresses));
		else if (line[i] == '>' && line[i + 1] == '>' && ++i)
			ft_lstadd_back1(commands, ft_lstnew1(">>", "append", addresses));
		else if (line[i] == '<')
			ft_lstadd_back1(commands, ft_lstnew1("<", "rd_in", addresses));
		else if (line[i] == '>')
			ft_lstadd_back1(commands, ft_lstnew1(">", "rd_out", addresses));
		else if (line[i] == '|')
			ft_lstadd_back1(commands, ft_lstnew1("|", "pipe", addresses));
		else if (line[i] == '\'' && check_quote(&line[i], '\'', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else if (line[i] == '\"' && check_quote(&line[i], '\"', NULL) == 1)
			ft_quotes(&line[i], commands, &i, addresses);
		else
			ft_word(&line[i], commands, &i, addresses);
		if (line[i])
			i++;
	}
}
