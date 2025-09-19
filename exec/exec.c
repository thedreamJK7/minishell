/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/19 11:01:32 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *arg)
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

int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	if (cmd->cmd.cmd && !is_builtin(cmd->cmd.cmd[0]))
		return (exec_builtin(shell, cmd->cmd.cmd));
	return (exec_non_builtin(cmd, shell));
}

int	execute(t_node *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		return (exec_pipe(node, shell));
		printf("return from pipe");
	}
	else
	{
		return(exec_simple_command(node, shell));
		printf("return from simple command");
	}
}
