/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/09 11:12:12 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *arg)
{
	if (!arg)
		return (1);
	if (!ft_strncmp(arg, "echo", ft_strlen("echo"))
		|| !ft_strncmp(arg, "cd", ft_strlen("cd"))
		|| !ft_strncmp(arg, "exit", ft_strlen("exit"))
		|| !ft_strncmp(arg, "pwd", ft_strlen("pwd"))
		|| !ft_strncmp(arg, "export", ft_strlen("export"))
		|| !ft_strncmp(arg, "unset", ft_strlen("unset"))
		|| !ft_strncmp(arg, "env", ft_strlen("env")))
		return (0);
	return (1);
}

int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	if (!is_builtin(cmd->cmd.cmd[0]))
		return (exec_builtin(cmd->cmd.cmd));
	exec_non_builtin(cmd);
	return (0);
}

int	execute(t_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == PIPE)
		return (exec_pipe(node, shell));
	else
		return(exec_simple_command(node, shell));
	return (0);
}
