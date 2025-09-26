/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:27:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/26 12:20:40 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	close_heredoc_fd(t_node *node)
{
	if (node->cmd.heredoc_fd == -1)
		return ;
	if (node->cmd.heredoc_fd)
		close(node->cmd.heredoc_fd);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
}

int		check_access(char *path)
{
	struct stat	statbuf;

	if (!lstat(path, &statbuf))
	{
		if (!S_ISDIR(statbuf.st_mode) && !access(path, X_OK))
			return (0);
	}
	return (1);
}

int		check_dir(char *path, int *flag)
{
	struct stat	statbuf;

	if (lstat(path, &statbuf) == -1)
	{
		if (errno == EACCES)
			*flag = 1;
		return (1);
	}
	if (S_ISDIR(statbuf.st_mode))
		return (0);
	if (errno == EACCES)
		*flag = 1;
	return (1);
}

int	print_error_cmd(int flag, char *cmd_name)
{
	if (flag == 1)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": Permission denied\n", STDERR_FILENO),  COMMAND_NOT_EXECUTABLE);
	else if (flag == 2)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": Is a directory\n", STDERR_FILENO), COMMAND_NOT_EXECUTABLE);
	else
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": command not found\n", STDERR_FILENO), COMMAND_NOT_FOUND);
}

int	print_error_path(int flag, char *cmd_name)
{
	if (flag == 1)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": Permission denied\n", STDERR_FILENO),  COMMAND_NOT_EXECUTABLE);
	else if (flag == 2)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": Is a directory\n", STDERR_FILENO), COMMAND_NOT_EXECUTABLE);
	else
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), ft_putstr_fd(": No such file or directory\n", STDERR_FILENO), COMMAND_NOT_FOUND);
}

int	count_cmd(t_node *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd.cmd[i])
		i++;
	return (i);
}