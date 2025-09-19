/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:30:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/18 18:36:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	write_to_pipe(t_redir_token *redir, int pipe_w)
{
	char	*input;
	int		len_lim;

	while (!g_sig_received)
	{
		input = readline("> ");
		if (!input)
		{
			if (g_sig_received == 1)
				return (close(pipe_w), 130);
	//		printf("Exit heredoc");
			break ;
		}
		if (*input)
			add_history(input);
		len_lim = ft_strlen(redir->file);
		if (!ft_strncmp(input, redir->file, len_lim) && (!input[len_lim] || input[len_lim] == '\n'))
		{
			free(input);
			break ;
		}
		if (write(pipe_w, input, ft_strlen(input)) == -1 || write(pipe_w, "\n", 1) == -1)
			return (free(input), close(pipe_w), perror("Write"), GENERAL_ERROR);
		free(input);
	}
	return (close(pipe_w), 0);
}

int	exec_heredoc(t_redir_token *redir, int *in_fd)
{
	int		pfd[2];
	int		pid;
	int		status;

	if (pipe(pfd) == -1)
		return (perror("Pipe"), GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("Fork"), GENERAL_ERROR);
	else if (!pid)
	{
		g_sig_received = 0;
		close(pfd[0]);
		signal(SIGINT, signal_handler_exit);
		exit(write_to_pipe(redir, pfd[1]));
	}
//	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_wait);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_main);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		if (WEXITSTATUS(status) == 130)
			g_sig_received = 1;
		return (close(pfd[0]), WEXITSTATUS(status));
	}
	*in_fd = pfd[0];
	return (0);
}