/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:47:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/11 12:44:35 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pfd[2];
	int	pid[2];
	int	status;

	if (pipe(pfd) == -1)
	{
		shell->exit_code = GENERAL_ERROR;
		return (perror("Pipe"), shell->exit_code);
	}
	pid[0] = fork();
	if (pid[0] == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		shell->exit_code = GENERAL_ERROR;
		return (perror("Fork"), shell->exit_code);
	}
	else if (!pid[0])
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execution(pipe_node->pipe.left);
		exit(shell->exit_code);
	}
	else
	{
		pid[1] = fork();
		if (pid[1] == -1)
		{
			close(pfd[0]);
			close(pfd[1]);
			waitpid(pid[0], NULL, 0);
			shell->exit_code = GENERAL_ERROR;
			return (perror("Fork"), shell->exit_code);
		}
		else if (!pid[1])
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			execution(pipe_node->pipe.right);
			exit(shell->exit_code);
		}
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_code = 128 + WTERMSIG(status);
		return (shell->exit_code);
	}
}