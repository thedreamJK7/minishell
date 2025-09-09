/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/09 10:56:56 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**copy_envir(void)
{
	extern char	**environ;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (environ[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(environ[j]);
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	clean_env_array(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	main(void)
{
	char	*input;
	t_shell	shell;

	setenv("HOME", "/test/home", 1);
    setenv("USER", "testuser", 1);
    setenv("PATH", "/usr/bin:/bin", 1);
    setenv("PWD", "/test/current", 1);
	shell.env = copy_envir();
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
		ft_parse(&input, &shell);
		free(input);
	}
	clean_env_array(shell.env);//clean up the created env array
	return (0);
}
