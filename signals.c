/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/05/01 16:33:39 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status(int exit_status)
{
    static int n;
    
    if (exit_status != -1)
        n = exit_status;
    return (n);
}

void run_signals(int flag)
{
    if(flag == 1)
    {
        rl_catch_signals = 0;
        signal(SIGINT, ctr_c);
    }   
    else
        signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void ctr_d(void)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
}

void ctr_c(int sig)
{
    write(1,"\n",1);
    if(sig == SIGINT)
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        exit_status(1);
    }
}