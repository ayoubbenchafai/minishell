/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/25 18:30:53 by aben-cha         ###   ########.fr       */
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

void	signal_exec(void)
{
	// if (signal(SIGINT, SIG_DFL) == SIG_ERR
	// 	|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	// 	return (exit_status(1));
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void ctr_d(void)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
}
// void	exit_status(int exit_status)
// {
// 	get_exit_status = exit_status;
// }

void ctr_c(int sig)
{
    // (void)sig;
    if(sig == SIGINT)
    {
        write(1,"\n",1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        exit_status(1);
        // get_exit_status = 1;
    }
}