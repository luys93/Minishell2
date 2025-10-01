/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:42:20 by lluciani          #+#    #+#             */
/*   Updated: 2025/09/27 15:34:05 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_handler(int sigtype, void (*f_handler)(int s))
{
	struct sigaction	sa;

	sa.sa_handler = f_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sigtype, &sa, NULL) == -1)
	{
		write(2, "Error: sigemptyset\n", 20);
		return (1);
	}
	return (0);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	g_status_signal = SIGINT;
	exit(1);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (signal_handler(SIGQUIT, SIG_IGN))
		return ;
	g_status_signal = SIGQUIT;
	kill(0, SIGQUIT);
	write(2, "Quit\n", 5);
}

void	sigint_handler(int sig)
{
	extern unsigned long	rl_readline_state;

	(void)sig;
	g_status_signal = SIGINT;
	write(2, "\n", 1);
	rl_on_new_line();
	/*rl_replace_line("", 0);
	if (rl_readline_state & RL_STATE_READCMD)
		rl_redisplay();*/
}
