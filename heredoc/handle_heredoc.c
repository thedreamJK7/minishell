/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:30:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/27 18:01:07 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_write(char *input, t_shell *shell, int pipe_w)
{
	char	*exp_input;

	exp_input = exp_heredoc(input, shell);
	free(input);
	if (write(pipe_w, exp_input, ft_strlen(exp_input)) == -1 || \
		write(pipe_w, "\n", 1) == -1)
		return (free(exp_input), close(pipe_w), perror("Write"), GENERAL_ERROR);
	free(exp_input);
	return (0);
}

void	print_warning(char *s)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", \
				STDOUT_FILENO);
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putstr_fd("')\n", STDOUT_FILENO);
}

int	process_input(t_redir_token *redir, t_shell *shell, int pipe_w)
{
	char	*input;
	int		ret;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			print_warning(redir->file);
			break ;
		}
		if (*input)
			add_history(input);
		if (!ft_strcmp(input, redir->file))
		{
			free(input);
			break ;
		}
		ret = expand_write(input, shell, pipe_w);
		if (ret)
			return (ret);
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
		close(pfd[0]);
		signal(SIGINT, signal_handler_exit);
		exit(process_input(redir, shell, pfd[1]));
	}
	signal(SIGINT, signal_handler_wait);
	close(pfd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_main);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (close(pfd[0]), WEXITSTATUS(status));
	*in_fd = pfd[0];
	return (0);
}

void	check_heredoc(t_node *node, t_shell *shell)
{
	t_redir_token	*tmp;

	tmp = node->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == HEREDOC)
		{
			if (node->cmd.heredoc_fd != -1)
				close(node->cmd.heredoc_fd);
			shell->exit_code = exec_heredoc(tmp, shell, &node->cmd.heredoc_fd);
			if (node->cmd.heredoc_fd == -1)
			{
				shell->exit_code = 130;
				g_sig_received = 1;
				return ;
			}
		}
		tmp = tmp->next;
	}
}

void	find_heredoc(t_node *node, t_shell *shell)
{
	if (!node | (g_sig_received == 1))
		return ;
	if (node->type == PIPE)
	{
		find_heredoc(node->pipe.left, shell);
		find_heredoc(node->pipe.right, shell);
	}
	else
	{
		if (node->cmd.redir_token)
			check_heredoc(node, shell);
	}
}
