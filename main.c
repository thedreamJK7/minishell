/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/11 18:44:51 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	
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
		ft_parse(&input, &shell);
		free(input);
	}
	cleanShell(shell);
	return (0);
}
