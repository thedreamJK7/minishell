/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:08 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/23 09:45:48 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_shell *shell, char **cmd)
{
	int	bool;

	bool = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		bool = builtin_echo(shell, cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		bool = builtin_pwd(cmd);
	if (!ft_strcmp(cmd[0], "export"))
		bool = builtin_export(shell, cmd);
	if (!ft_strcmp(cmd[0], "cd"))
		bool = builtin_cd(shell, cmd);
	if (!ft_strcmp(cmd[0], "exit"))
		bool = builtin_exit(shell, cmd);
	if (!ft_strcmp(cmd[0], "env"))
		bool = builtin_env(shell, cmd);
	if (!ft_strcmp(cmd[0], "unset"))
		bool = builtin_unset(shell, cmd);
	return (bool);
}
