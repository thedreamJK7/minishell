/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:08 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 14:34:46 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void restore_fds(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    dup2(err, STDERR_FILENO);
    close(in);
    close(out);
    close(err);
}

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

int exec_child_builtin(t_node *node, t_shell *shell)
{
	int	status;
	int pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), GENERAL_ERROR);
	if (!pid)
	{
		if (setup_redirections(node))
			exit (1);
		exit(exec_builtin(shell, node->cmd.cmd));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_code = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	return (1);
}

int	exec_normal_builtin(t_node *cmd, t_shell *shell)
{
	int saved_in;
	int saved_out;
	int saved_err;
	int exit_code;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	exit_code = 1;
	if (cmd->cmd.redir_token && setup_redirections(cmd))
		return (restore_fds(saved_in, saved_out, saved_err), exit_code);
	restore_fds(saved_in, saved_out, saved_err);
	exit_code = exec_builtin(shell, cmd->cmd.cmd);
	return (exit_code);
}
