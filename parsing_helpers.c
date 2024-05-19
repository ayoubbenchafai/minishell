/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:25:42 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/18 16:35:42 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '|')
			flag = 1;
		i++;
	}
	return (flag);
}

int	special_char(char c)
{
	char	*special;
	int		i;

	special = " <>&|;\'\"\t";
	i = 0;
	while (special[i])
	{
		if (special[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	quotes_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && check_quote(&line[i], '\'', &i) == 0)
		{
			printf("quote error\n");
			exit_status(127);
			free(line);
			return (1);
		}
		if (line[i] == '\"' && check_quote(&line[i], '\"', &i) == 0)
		{
			printf("quote error\n");
			exit_status(127);
			free(line);
			return (1);
		}
		if (line[i])
			i++;
	}
	return (0);
}

int	check_quote(char *line, char c,	int *offset)
{
	int	i;
	int	j;
	int	last;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			last = i;
			j++;
		}
		i++;
	}
	if (j % 2 == 0)
	{
		if (offset)
			*offset += last;
		return (1);
	}
	return (0);
}
