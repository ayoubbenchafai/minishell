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

#include "libft.h"

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

static	int	alloc_move(char *original, char c, char **d_arr, int *i)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (*i < word_count(original, c))
	{
		letters_count(original, c, &end, &start);
		d_arr[*i] = (char *)malloc(end - start + 1);
		if (d_arr[*i] == NULL)
			return (0);
		ft_memmove(d_arr[*i], &original[start], end - start);
		d_arr[*i][end - start] = '\0';
		(*i)++;
	}
	return (1);
}

char	**ft_split(char *original, char c)
{
	char	**d_arr;
	int		i;

	if (!original)
		return (NULL);
	i = 0;
	d_arr = (char **)malloc((word_count(original, c) + 1) * sizeof(char *));
	if (d_arr == NULL)
		return (d_arr);
	d_arr[word_count(original, c)] = NULL;
	if (!(alloc_move(original, c, d_arr, &i)))
	{
		while (i >= 0)
		{
			free(d_arr[i]);
			i--;
		}
		free(d_arr);
		return (NULL);
	}
	return (d_arr);
}

// int main()
// {
// 	int i = 0;
// 	char **results = ft_split("NULL", );
// 	while (results[i])
// 	{
// 		printf("%s", results[i]);
// 		i++;
// 	}
// 	return (0);
// }