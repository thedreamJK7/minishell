/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:14 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/19 14:37:13 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_exit(int sig)
{
	(void)sig;
//	g_sig_received = 1;
	write(STDOUT_FILENO, "\n", 1);
//	printf("exit!\n");
	exit(130);
}

void	signal_handler_wait(int sig)
{
	(void)sig;
//	g_sig_received = 1;
//	write(STDOUT_FILENO, "\n", 1);
//	printf("wait!\n");
}

void	signal_handler_main(int sig)
{
//	printf("welcome to main handler\n");
	(void)sig;
//	g_sig_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void(*signal_handler)(int))
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
