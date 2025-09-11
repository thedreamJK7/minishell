/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/11 17:43:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_node	*node;
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.exit_code = 1;
	if (!shell.env)
		printf("No shell->env");//create environment for test
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
		node = ft_parse(&input, &shell);
		if (!node)
		{
			free(input);
			continue ;
		}
		execute(node, &shell, envp);
		freeAST(node);
		free(input);
	}
	return (0);
}
