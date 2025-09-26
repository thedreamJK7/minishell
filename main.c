/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/26 11:18:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

sig_atomic_t	g_sig_received = 0;

static void	shell_loop(t_shell **shell)
{
	char	*input;
	t_token	*token_list;

	setup_signals(signal_handler_main);
	while (1)
	{
		input = readline("minishell$ ");
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
		token_list = ft_tokenize(input, (*shell));
		if (!token_list)
			continue ;
		(*shell)->nodes = ft_parse(token_list);
		if (!(*shell)->nodes)
		{
			free(input);
			clean_tokens(&token_list, 0);
			(*shell)->exit_code = 0;
			continue ;
		}
		clean_tokens(&token_list, 0);
		find_heredoc((*shell)->nodes, *shell);
		if (g_sig_received == 1)
		{
			free_ast((*shell)->nodes);
			free(input);
			continue ;
		}
		(*shell)->exit_code = execute((*shell)->nodes, *shell);
		free_ast((*shell)->nodes);
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
	clean_shell(shell);
	rl_clear_history();
	return (0);
}
