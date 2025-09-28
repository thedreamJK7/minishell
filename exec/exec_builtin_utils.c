/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:17:35 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 14:36:27 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	setup_in_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

static int	setup_out_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

static int	setup_append_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

static int	setup_heredoc_redir(int heredoc_fd, t_redir_token *redir)
{
	int	fd;

	fd = heredoc_fd;
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

int setup_redirections(t_node *nodes)
{
	t_redir_token	*tmp;
	int				ret;

	tmp = nodes->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == IN)
			ret = setup_in_redir(tmp);
		else if (tmp->redir_type == OUT)
			ret = setup_out_redir(tmp);
		else if (tmp->redir_type == APPEND)
			ret = setup_append_redir(tmp);
		else if (tmp->redir_type == HEREDOC)
			ret = setup_heredoc_redir(nodes->cmd.heredoc_fd, tmp);
		if (ret != 0)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}