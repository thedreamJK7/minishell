/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 19:50:50 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_builtin(char *arg)
{
	if (!arg)
		return (1);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (0);
	return (1);
}

static int	is_child_builtin(char *arg)
{
	if (!ft_strcmp(arg, "env") || !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "echo"))
		return (0);
	return (1);
}

int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	if (cmd->cmd.cmd && !is_builtin(cmd->cmd.cmd[0]))
	{
		if (!is_child_builtin(cmd->cmd.cmd[0]))
			return (exec_child_builtin(cmd, shell));
		else
			return (exec_normal_builtin(cmd, shell));
	}
	else
		return (exec_non_builtin(cmd, shell));
}

void	execute(t_node *node, t_shell *shell)
{
	if (node->type == PIPE)
		shell->exit_code = exec_pipe(node, shell);
	else
		shell->exit_code = exec_simple_command(node, shell);
}
