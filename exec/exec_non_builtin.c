/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/11 12:44:41 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_non_builtin(t_node *cmd, t_shell *shell)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		shell->exit_code = GENERAL_ERROR;
		return (perror("fork"), shell->exit_code);
	}
	else if (!pid)
	{
		//child_process
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
	return (shell->exit_code);
}