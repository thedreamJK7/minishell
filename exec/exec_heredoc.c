/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/23 09:40:40 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	write_to_pipe(t_redir_token *redir, t_shell *shell, int pipe_w)
{
	char	*input;
	int		len_lim;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
//			if (g_sig_received == 1)
//				return (close(pipe_w), 130);
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
		char *exp_input = exp_heredoc(input, shell);
		free(input);
		if (write(pipe_w, exp_input, ft_strlen(exp_input)) == -1 || write(pipe_w, "\n", 1) == -1)
		{
			printf("write fail\n");
			return (free(exp_input), close(pipe_w), perror("Write"), 0);
		}
		free(exp_input);
	}
	return (close(pipe_w), 0);
}

int	exec_heredoc(t_redir_token *redir, t_shell *shell, int *in_fd)
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
//		g_sig_received = 0;
//		signal(SIGPIPE, SIG_IGN);
		close(pfd[0]);
		signal(SIGINT, signal_handler_exit);
		exit(write_to_pipe(redir, shell, pfd[1]));
	}
//	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_wait);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_main);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
//		if (WEXITSTATUS(status) == 130)
//			g_sig_received = 1;
		return (close(pfd[0]), WEXITSTATUS(status));
	}
	*in_fd = pfd[0];
	return (0);
}

void	check_heredoc(t_redir_token *redir, t_shell *shell)
{
	t_redir_token	*tmp;

	tmp = redir;
	while (redir)
	{
		if(redir->redir_type == HEREDOC)
		{
			shell->exit_code = exec_heredoc(redir, shell, &redir->heredoc_fd);
			if (redir->heredoc_fd == -1 && shell->exit_code)
				printf("heredoc invalid");
		}
		redir = redir->next;
	}
	redir = tmp;
}

void	find_heredoc(t_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == PIPE)
	{
		find_heredoc(node->pipe.left, shell);
		find_heredoc(node->pipe.right, shell);
	}
	else
	{
		if (node->cmd.redir_token)
			check_heredoc(node->cmd.redir_token, shell);
	}
}






