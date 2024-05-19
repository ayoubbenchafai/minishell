/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:52:30 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/16 16:52:58 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_ft_strdup(const char *s)
{
    char	*ptr;
    size_t	len;

    len = ft_strlen(s);
    ptr = malloc(len + 1);
    if (ptr == NULL)
        return (NULL);
    ft_strlcpy(ptr, s, len + 1);
    return (ptr);
}