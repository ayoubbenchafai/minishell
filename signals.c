/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/17 15:46:30 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_signals(void)
{
    // get_exit_status = 0;
    rl_catch_signals = 0;
    signal(SIGINT, ctr_c);
    signal(SIGQUIT, bach_slash);
}

void ctr_d(void)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
}

void ctr_c(int sig)
{
    printf("int sig : %d\n", sig);
    if(sig == SIGINT)
    {
        write(1,"\n",1);
        get_exit_status = 1;
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}
void bach_slash(int sig)
{
    if (sig == SIGQUIT)
    {
        signal(SIGQUIT, SIG_IGN); 
        get_exit_status = 1;
    }
}

//$_ the last argument 