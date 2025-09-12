/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/12 12:54:06 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_node	*node;
	
	(void)argc;
	(void)argv;
	shell = init_envp(envp);
	if (!shell)
		return (printf("Failed to inishilize shell"), 1);
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			exit(1);
		}
		if (*input)
			add_history(input);
		node = ft_parse(&input, shell);
		if (!node)
		{
			free(input);
			continue ;
		}
		//execute(node, &shell);
		freeAST(node);
		free(input);
	}
	cleanShell(shell);
	return (0);
}
