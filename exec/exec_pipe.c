/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:47:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/26 11:00:12 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pfd[2];
	int	pid[2];
	int	status1;
	int	status2;

	if (pipe(pfd) == -1)
	{
		shell->exit_code = GENERAL_ERROR;
		return (perror("Pipe"), shell->exit_code);
	}
	pid[0] = fork();
//	signal(SIGPIPE, SIG_IGN);
	if (pid[0] == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		shell->exit_code = GENERAL_ERROR;
		return (perror("Fork"), shell->exit_code);
	}
	else if (!pid[0])
	{
//		signal(SIGPIPE, SIG_IGN);
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute(pipe_node->pipe.left, shell);
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
			execute(pipe_node->pipe.right, shell);
			exit(shell->exit_code);
		}
		close(pfd[0]);
		close(pfd[1]);
		setup_signals(signal_handler_wait);
		waitpid(pid[1], &status2, 0);
		waitpid(pid[0], &status1, 0);
		if (WIFEXITED(status2))
		{
			if (WEXITSTATUS(status2) == 0 && WTERMSIG(status1) == 13 && g_sig_received == 2)
			{
				write(STDOUT_FILENO, "\n", 1);
				g_sig_received = 0;
			}
			shell->exit_code = WEXITSTATUS(status2);
		}
		else if (WIFSIGNALED(status2))
		{
			shell->exit_code = 128 + WTERMSIG(status2);
		}
		setup_signals(signal_handler_main);
		return (shell->exit_code);
	}
}