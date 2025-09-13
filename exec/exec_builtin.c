/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:08 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/13 22:12:11 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_shell *shell, char **cmd)
{
	int	bool;

	bool = 0;
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")))
		bool = builtin_pwd(cmd);
	if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
		bool = builtin_export(shell->env_list, cmd);
	if (!ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
		bool = builtin_cd(shell, cmd);
	return (bool);
}
