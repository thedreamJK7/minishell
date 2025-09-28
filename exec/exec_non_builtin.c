/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/27 19:43:28 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_in_out_append(int *fd, t_redir_token *tmp)
{
	if (*fd != -1)
		close (*fd);
	if (tmp->redir_type == IN)
		*fd = open(tmp->file, O_RDONLY);
	else if (tmp->redir_type == OUT)
		*fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir_type == APPEND)
		*fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (perror(tmp->file), GENERAL_ERROR);
	return (0);
}

int	open_files(t_node *node, int *in_fd, int *out_fd)
{
	t_redir_token	*tmp;
	int				ret;

	tmp = node->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == HEREDOC)
			*in_fd = node->cmd.heredoc_fd;
		else if (tmp->redir_type == IN)
			ret = open_outfile(in_fd, tmp);
		else
			ret = open_outfile(out_fd, tmp);
		if (ret)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}

int	concat_path(char *cmd_name, char **dirs, char **path)
{
	int		i;
	int		flag;
	char	*tmp;

	i = -1;
	flag = 0;
	while (dirs[++i])
	{
		*path = ft_strjoin(dirs[i], "/");
		if (!*path)
			return (perror("Malloc"), GENERAL_ERROR);
		tmp = ft_strjoin(*path, cmd_name);
		if (!tmp)
			return (free(*path), perror("Malloc"), GENERAL_ERROR);
		free(*path);
		*path = tmp;
		if (!check_access(*path))
			return (0);
		check_dir_cmd(*path, &flag);
		free(*path);
	}
	return (print_error_cmd(flag, cmd_name));
}

int	check_full_path(char *cmd_path, char **path)
{
	int	flag;

	flag = 0;
	if (!check_access(cmd_path))
	{
		*path = cmd_path;
		return (0);
	}
	if (!check_dir_path(cmd_path, &flag))
		flag = 2;
	return (print_error_path(flag, cmd_path));
}

int	find_cmd_path(char **cmd, char **path, t_shell *shell)
{
	char	*path_env;
	char	**dirs;
	int		ret;

	if (ft_strchr(cmd[0], '/'))
		return (check_full_path(cmd[0], path));
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (ft_putstr_fd(cmd[0], STDERR_FILENO), \
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO), \
		COMMAND_NOT_FOUND);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (ft_putstr_fd("Path split failed", STDERR_FILENO), \
		free(path_env), GENERAL_ERROR);
	ret = concat_path(cmd[0], dirs, path);
	if (ret)
		return (clean_array(dirs), ret);
	clean_array(dirs);
	return (0);
}

void	redir_child(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

int	exec_child(t_node *cmd, int in_fd, int out_fd, t_shell *shell)
{
	char	*path;
	char	**env;

	setup_signals(signal_handler_exit);
	path = NULL;
	redir_child(in_fd, out_fd);
	shell->exit_code = find_cmd_path(cmd->cmd.cmd, &path, shell);
	if (shell->exit_code)
		exit(shell->exit_code);
	env = envp_to_array(shell->env_list);
	if (!env)
	{
		ft_putstr_fd("Environment not found", STDERR_FILENO);
		free(path);
		exit(GENERAL_ERROR);
	}
	if (execve(path, cmd->cmd.cmd, env) == -1)
	{
		perror("Execve");
		free(path);
		clean_array(env);
		exit(GENERAL_ERROR);
	}
	return (0);
}

int	exec_cmd(t_node *cmd, t_shell *shell, int in_fd, int out_fd)
{
	int	pid;
	int	status;

	pid = -1;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fd(in_fd, out_fd), GENERAL_ERROR);
	else if (!pid)
		exec_child(cmd, in_fd, out_fd, shell);
	setup_signals(signal_handler_wait);
	close_fd(in_fd, out_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_code = WEXITSTATUS(status);
		return (setup_signals(signal_handler_main), shell->exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
			write(STDOUT_FILENO, "\n", 1);
		shell->exit_code = 128 + WTERMSIG(status);
		return (setup_signals(signal_handler_main), shell->exit_code);
	}
	return (0);
}

int	exec_non_builtin(t_node *cmd, t_shell *shell)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (cmd->cmd.redir_token)
	{
		shell->exit_code = open_files(cmd, &in_fd, &out_fd);
		if (shell->exit_code)
			return (close_heredoc_fd(cmd), close_fd(in_fd, out_fd), \
			shell->exit_code);
	}
	if (!cmd->cmd.cmd)
	{
		shell->exit_code = 0;
		return (close_fd(in_fd, out_fd), shell->exit_code);
	}
	return (exec_cmd(cmd, shell, in_fd, out_fd));
}
