/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:42:40 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 14:44:14 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	print_exp(t_node *node)
{
	t_shell	shell;

	setenv("HOME", "/test/home", 1);
    setenv("USER", "testuser", 1);
    setenv("PATH", "/usr/bin:/bin", 1);
    setenv("PWD", "/test/current", 1);
	shell.env = copy_envir();
	if (!shell.env)
		printf("No shell->env");
	//ft_expand(node, &shell);
	print_ast(node, 1);
	clean_env_array(shell.env);
}