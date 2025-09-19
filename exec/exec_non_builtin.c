/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/19 15:09:12 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files(t_redir_token *redir, int *in_fd, int *out_fd)
{
	int	ret;

	ret = 0;
	while (redir)
	{
		if (redir->redir_type == IN)
		{
			if (*in_fd != -1)
				close (*in_fd);
			*in_fd = open(redir->file, O_RDONLY);
			if (*in_fd == -1)
				return (perror(redir->file), GENERAL_ERROR);
		}
		else if (redir->redir_type == OUT || redir->redir_type == APPEND)
		{
			if (*out_fd != -1)
				close (*out_fd);
			if (redir->redir_type == OUT)
				*out_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redir->redir_type == APPEND)
				*out_fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*out_fd == -1)
				return (perror(redir->file), GENERAL_ERROR);
		}
		redir = redir->next;
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
		else if (check_access(*path) == COMMAND_NOT_EXECUTABLE)
			flag = 1;
	}
	free(*path);
	if (flag)
		return (COMMAND_NOT_EXECUTABLE);
	return (COMMAND_NOT_FOUND);
}

int	find_cmd_path(char **cmd, char **path, t_shell *shell)
{
	char	*path_env;
	char	**dirs;
	int		ret;

	if (ft_strchr(cmd[0], '/'))
	{
		ret = check_access(cmd[0]);
		if (!ret)
			*path = cmd[0];
		return (ret);
	}
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (ft_putstr_fd("Path not found", STDERR_FILENO), GENERAL_ERROR);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (ft_putstr_fd("Path split failed", STDERR_FILENO), GENERAL_ERROR);
	ret = concat_path(cmd[0], dirs, path);
	if (ret)
		return (ret);
	clean_array(dirs);
	return (0);
}

int	exec_child(t_node *cmd, int in_fd, int out_fd, t_shell *shell)
{
	char	*path;
	char	**env;

	path = NULL;
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

int	exec_non_builtin(t_node *cmd, t_shell *shell)
{
	int	pid;
	int	status;
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	pid = -1;
	if (cmd->cmd.redir_token && cmd->cmd.redir_token->redir_type == HEREDOC)
	{
		shell->exit_code = exec_heredoc(cmd->cmd.redir_token, &in_fd);
		if (shell->exit_code)
			return (close_fd(in_fd, out_fd), shell->exit_code);
	}
	
	shell->exit_code = open_files(cmd->cmd.redir_token, &in_fd, &out_fd);
	if (shell->exit_code)
		return (close_fd(in_fd, out_fd), shell->exit_code);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fd(in_fd, out_fd), GENERAL_ERROR);
	else if (!pid)
	{
//		signal(SIGINT, SIG_DFL);
		setup_signals(signal_handler_exit);
		exec_child(cmd, in_fd, out_fd, shell);
	}
	setup_signals(signal_handler_wait);
//	signal(SIGINT, SIG_IGN);
	close_fd(in_fd, out_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		shell->exit_code = WEXITSTATUS(status);
		return (setup_signals(signal_handler_main), WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
		{
//			printf("cmd: %d\n", g_sig_received);
			write(STDOUT_FILENO, "\n", 1);
//			g_sig_received = 0;
		}
		shell->exit_code =  128 + WTERMSIG(status);
		return (setup_signals(signal_handler_main), shell->exit_code);
	}
	return (0);
}
