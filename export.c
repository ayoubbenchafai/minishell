/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:33:08 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/17 03:24:20 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern char **environ;

void export_command(char **env, char *value)
{
    char **env = NULL;

    env = array_append(env, value);
}