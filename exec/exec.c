/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/24 17:55:34 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int setup_redirections(t_redir_token *redirs)
{
	t_redir_token	*tmp;
	int				fd;

	tmp = redirs;
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
			fd = tmp->heredoc_fd;
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

int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	// if (cmd->cmd.redir_token)
	// 	return (exec_non_builtin(cmd, shell));
	if (cmd->cmd.cmd && !is_builtin(cmd->cmd.cmd[0]))
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
			if (setup_redirections(cmd->cmd.redir_token))
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
		return (exec_non_builtin(cmd, shell));
	return (shell->exit_code);
}

int	execute(t_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		return (exec_pipe(node, shell));
	}
	else
	{
		return(exec_simple_command(node, shell));
	}
}
