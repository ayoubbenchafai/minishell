/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:19:35 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/12 15:46:49 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;
	i = 0;

	while (s && s[i])
		i++;
	return (i);
}
int get_equal(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if(s[i] == '=')
            return i;
        i++;
    }
    return 0;
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (!n)
		return (0);
	if(!s1 && s2)
		return (-s2[0]);
	if(!s2 && s1)
		return (s1[0]);
	if (!s1 && !s2)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] && i < n)
		return (s1[i]);
	else if (s2[i] && i < n)
		return (-s2[i]);
	return (0);
}
// int get_size(char **env, char *var)
// {
// 	int	i;
// 	int	size;

// 	i = 0;
// 	size = get_equal(var);
//     if (size == 0)
//         return (ft_strlen(var));
// 	while (env && env[i])
// 	{
//         // if (var[len - 1] == '+' && var[len] == '=')
//             size = get_best_size(env[i]);
// 		if (!ft_strncmp(env[i], var, size))
//         {
// 			size = get_equal(env[i]);
//             return (size);
//         }
// 		i++;
// 	}
// 	return (size);
// }

int compare_size(char *var, char *env)
{
	int size = get_equal(var);
	//size != 0

	if(var[size - 1] == '+' && var[size] == '=' && !get_equal(env))
	{
		printf("test1\n");
		if (get_equal(var) - 1 == ft_strlen(env))
			return (1);
	}
	if(var[size - 1] == '+' && var[size] == '=' && get_equal(env))
	{
		printf("test2\n");

		if (get_equal(var) - 1 == get_equal(env))
			return (1);
	}
	else if(get_equal(var) && !get_equal(env))
	{
		printf("test3\n");
		if (get_equal(var) == ft_strlen(env))
			return (1);
	}
	else if(get_equal(var) && get_equal(env))
	{
		printf("test4\n");
		if (get_equal(var) == get_equal(env))
			return (1);
	}
	
	return (0);
}

int compare_size1(char *var, char *env)
{
	if (get_equal(var) - 1 == ft_strlen(env))
	{
		printf("test1\n");
		return (1);
	}
	else if (get_equal(var) - 1 == get_equal(env))
	{
		printf("test2\n");
		return (1);
	}
	else if (get_equal(var) == ft_strlen(env))
	{
		printf("test3\n");
		return (1);
	}
	else if (get_equal(var) == get_equal(env))
	{
		printf("test4\n");
		return (1);
	}
	
	
	return (0);
}

int get_best_size(char *var)
{
    int j = 0;
    int size = get_equal(var);
    
    if (size == 0)
        j = ft_strlen(var);
    else
    {
        if (var[size - 1] == '+' && var[size] == '=')
            j = size - 1;            // j = size;
        else
            j = size;
    }
    return (j);
}

int	ft_strcmp(const char *s1,const char *s2)
{
	int i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
   
	printf("n = : %d\n", ft_strcmp("ayou", "ayou"));
	// printf("compare1 = %d\n", get_best_size("va"));
    return (0);
}

