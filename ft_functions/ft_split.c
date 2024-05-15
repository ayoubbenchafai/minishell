/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:34:02 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/08 23:11:36 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	word_count(char *original, char c)
{
	int	i;

	i = 0;
	while (*original)
	{
		while (*original == c && *original)
			original++;
		if (*original)
			i++;
		while (*original != c && *original)
			original++;
	}
	return (i);
}

static	void	letters_count(char *original, char c, int *end, int *start)
{
	while (original[*end] == c && original[*end])
		(*end)++;
	*start = *end;
	while (original[*end] != c && original[*end])
		(*end)++;
}

static int	alloc_move(char *original, char **d_arr, t_args *args, t_node **add)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (args->i < word_count(original, args->c))
	{
		letters_count(original, args->c, &end, &start);
		d_arr[args->i] = ft_malloc(end - start + 1, add);
		if (d_arr[args->i] == NULL)
			return (0);
		ft_memmove(d_arr[args->i], &original[start], end - start);
		d_arr[args->i][end - start] = '\0';
		args->i++;
	}
	return (1);
}

char	**ft_split(char *original, char c, t_node **addr)
{
	char		**d_arr;
	int			i;
	t_args		args;

	if (!original)
		return (NULL);
	i = 0;
	d_arr = ft_malloc((word_count(original, c) + 1) * sizeof(char *), addr);
	if (d_arr == NULL)
		return (d_arr);
	d_arr[word_count(original, c)] = NULL;
	args.c = c;
	args.i = 0;
	if (!alloc_move(original, d_arr, &args, addr))
		return (NULL);
	return (d_arr);
}
