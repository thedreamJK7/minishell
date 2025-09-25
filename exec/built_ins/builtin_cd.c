/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:50:16 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/25 10:06:20 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_home(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (!home)
		return (1);
	if (chdir(home) == -1)
		return (perror("minishell: cd: No such file or directory"), 1);
	return (0);
}

int change_directory(char *arg)
{
	if (chdir(arg) == -1)
		return (perror("minishell: cd: No such file or directory"), 1);
	return (0);
}

void update_env_value(t_shell *shell, char *oldpwd, char *pwd)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (ft_strcmp(current->name, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(pwd);
		}
		else if (ft_strcmp(current->name, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(oldpwd);
		}
		current = current->next;
	}
}

int	builtin_cd(t_shell *shell, char **cmd)
{
	int		argc;
	char	*pwd;
	char	*oldpwd;

	argc = count_arguments(cmd + 1);
	if (argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd() error"), 1);
	if (argc == 0 && go_home(shell))
		return (1);
	if (argc == 1 && change_directory(cmd[1]))
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd() error"), free(oldpwd), 1);
	update_env_value(shell, oldpwd, pwd);
	return (free(oldpwd), free(pwd), 0);
}
