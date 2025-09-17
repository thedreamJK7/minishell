/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/17 18:22:13 by yingzhan         ###   ########.fr       */
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
			continue ;
		}
		execute(nodes, *shell);
		free_ast(nodes);
		free(input);
		g_sig_received = 0;
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
	setup_signals();
	shell_loop(&shell);
	rl_clear_history();
	clean_shell(shell);
	return (0);
}
