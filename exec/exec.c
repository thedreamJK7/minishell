/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 13:46:08 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int setup_redirections(t_node *nodes)
{
	t_redir_token	*tmp;
	int				fd;

	tmp = nodes->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == IN)
		{
			fd = open(tmp->file, O_RDONLY);
			if (fd == -1)
				return (perror(tmp->file), GENERAL_ERROR);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (tmp->redir_type == OUT)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(tmp->file), GENERAL_ERROR);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (tmp->redir_type == APPEND)
		{
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(tmp->file), GENERAL_ERROR);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (tmp->redir_type == HEREDOC)
		{
			fd = nodes->cmd.heredoc_fd;
			if (fd == -1)
				return (perror(tmp->file), GENERAL_ERROR);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_builtin(char *arg)
{
	if (!arg)
		return (1);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (0);
	return (1);
}

int	is_child_builtin(char *arg)
{
	if (!ft_strcmp(arg, "env") || !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "echo"))
		return (0);
	return (1);
}

void restore_fds(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    dup2(err, STDERR_FILENO);
    close(in);
    close(out);
    close(err);
}

int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	if (cmd->cmd.cmd && !is_builtin(cmd->cmd.cmd[0]))
	{
		if (!is_child_builtin(cmd->cmd.cmd[0]))
		{
			int	status;
			int pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return (GENERAL_ERROR);
			}
			if (!pid)
			{
				if (setup_redirections(cmd))
					exit (1);
				exit(exec_builtin(shell, cmd->cmd.cmd));
			}
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				shell->exit_code = WEXITSTATUS(status);
				return (WEXITSTATUS(status));
			}
		}
		else
		{
			int saved_in = dup(STDIN_FILENO);
			int saved_out = dup(STDOUT_FILENO);
			int saved_err = dup(STDERR_FILENO);

			if (cmd->cmd.redir_token && setup_redirections(cmd))
			{
				restore_fds(saved_in, saved_out, saved_err);
				return (1);
			}
			restore_fds(saved_in, saved_out, saved_err);
			int exit_code = exec_builtin(shell, cmd->cmd.cmd);
			return (exit_code);
		}
	}
	else
		return (exec_non_builtin(cmd, shell));
	return (shell->exit_code);
}

void	execute(t_node *node, t_shell *shell)
{
	if (node->type == PIPE)
		shell->exit_code = exec_pipe(node, shell);
	else
		shell->exit_code = exec_simple_command(node, shell);
}
