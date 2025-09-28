/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 14:45:44 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

static int	read_input(t_shell *shell, char **input)
{
	*input = readline("minishell$ ");
	if (g_sig_received == 1)
	{
		shell->exit_code = 130;
		g_sig_received = 0;
	}
	if (!*input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	if (**input)
		add_history(*input);
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;
	t_token	*token_list;

	while (1)
	{
		if (read_input(shell, &input))
			break ;
		token_list = ft_tokenize(input, shell);
		if (!token_list)
			continue ;
		shell->nodes = ft_parse(token_list, &shell->exit_code);
		if (!shell->nodes)
		{
			free(input);
			clean_tokens(&token_list, 0);
			continue ;
		}
		clean_tokens(&token_list, 0);
		find_heredoc(shell->nodes, shell);
		if (g_sig_received == 1)
		{
			free_ast(shell->nodes);
			free(input);
			continue ;
		}
		execute(shell->nodes, shell);
		free_ast(shell->nodes);
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
		return (ft_putstr_fd("Failed to initialize shell", \
				STDERR_FILENO), GENERAL_ERROR);
	setup_signals(signal_handler_main);
	shell_loop(shell);
	clean_shell(shell);
	rl_clear_history();
	return (0);
}
