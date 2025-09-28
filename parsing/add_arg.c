/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:24:03 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ensure_cmd_capacity(t_node *cmd, int count)
{
	if (!cmd->cmd.cmd)
	{
		cmd->cmd.cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
	}
	else
	{
		cmd->cmd.cmd = ft_realloc1(cmd->cmd.cmd,
				(count + 1) * sizeof(char *),
				(count + 2) * sizeof(char *));
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
	}
	return (0);
}

int	add_arg(t_node *cmd, t_token **list)
{
	int	i;

	i = 0;
	while (cmd->cmd.cmd && cmd->cmd.cmd[i])
		i++;
	if (ensure_cmd_capacity(cmd, i))
		return (1);
	if (!(*list)->value)
		cmd->cmd.cmd[i] = ft_strdup("");
	else
	{
		cmd->cmd.cmd[i] = ft_strdup((*list)->value);
		if (!cmd->cmd.cmd[i])
			return (printf(ALLOCATION_FAIL), 1);
	}
	cmd->cmd.cmd[i + 1] = NULL;
	*list = (*list)->next;
	return (0);
}
