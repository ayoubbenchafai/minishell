/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:19:35 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/08 16:22:27 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// int check_error(char *var)
// {
//     int i = 0;
//     int j;
//     int size;
    
//     if (var[i] == '_')
//         i++;
//     j = i;
//     if(!ft_isalpha(var[i]))
//         return (0);
//     size = get_equal(var);
//     while(var[i] && (size == 0))
//     {
//         if(var[i]!='_')
//             if (!ft_isalnum(var[i]))
//                 return (0);
//         i++;
//     }
//     i += j;
//     while(i < size)
//     {
//         if(var[i] != '_')
//         {
//             if(var[i] == '+' && var[i + 1])
//             {
//                 i++;
//                 if(var[i] == '=')
//                     break;
//                 else 
//                     return (0);
//             }
//         if (!ft_isalnum(var[i]))
//             return (0);
//         }
//         i++;
//     }
//     return (1);
// }

int main(int ac, char **av, char **envp)
{
    // char *var = "VAR=123";
    // printf("%d\n", check_error(var));

    int i = 0;
    while(envp[i])
    {
        if(!ft_strncmp(envp[i], s, st))
        i++;
    }
    return (0);
}
