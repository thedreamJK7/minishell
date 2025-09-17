/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/16 14:41:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_node	*node;

	(void)argc;
	(void)argv;
	shell = init_envp(envp);
	if (!shell)
		return (printf("Failed to initialize shell"), 1);
	input = NULL;
	setup_signals(signal_handler_main);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		node = ft_parse(&input, shell);
		if (!node)
		{
			free(input);
			continue ;
		}
		execute(node, shell);
		free_ast(node);
		free(input);
		g_sig_received = 0;
	}
	clean_shell(shell);
	return (0);
}
