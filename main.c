/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/23 09:47:36 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

static void	shell_loop(t_shell **shell)
{
	char	*input;
	t_node	*nodes;

	nodes = NULL;
	input = NULL;
	setup_signals(signal_handler_main);
	while (1)
	{
		input = readline("minishell$ ");
		if (g_sig_received == 1)
		{
			(*shell)->exit_code = 130;
			g_sig_received = 0;
		}
		if (g_sig_received == 1)
		{
			(*shell)->exit_code = 130;
			g_sig_received = 0;
		}
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*input)
			add_history(input);
		nodes = ft_parse(&input, *shell);
		if (!nodes)
		{
			free(input);
			(*shell)->exit_code = 1;
			(*shell)->exit_code = 1;
			continue ;
		}
		find_heredoc(nodes, *shell);
		find_heredoc(nodes, *shell);
		(*shell)->exit_code = execute(nodes, *shell);
		free_ast(nodes);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_envp(envp);
	if (!shell)
		return (printf("Failed to initialize shell"), 1);
	shell_loop(&shell);
	rl_clear_history();
	clean_shell(shell);
	return (0);
}
