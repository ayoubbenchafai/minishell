/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:33:08 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/16 23:33:23 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern char **environ;

void export_command(char *var, char *value) {
    char **env = environ;

    while (*env) 
    {
        var = *env;
        value = getenv(variable);
        if (value != NULL) {
            printf("%s=%s\n", variable, value);
        }
        env++;
    }
}