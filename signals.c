/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:34:38 by aben-cha          #+#    #+#             */
/*   Updated: 2024/04/23 16:50:37 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_signals(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, ctr_c);
    signal(SIGQUIT, bach_slash);
}

void	signal_exec(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR
		|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (exit_status(1));
}

void ctr_d(void)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
}
void	exit_status(int exit_status)
{
	get_exit_status = exit_status;
}

void ctr_c(int sig)
{
    // (void)sig;
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
        get_exit_status = 0;
        signal(SIGQUIT, SIG_IGN);
    }
}