/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/27 13:10:13 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_arg(t_node *cmd, t_token **list)
{
	int 	i;

	if (!cmd->cmd.cmd)
	{
		i = 0;
		cmd->cmd.cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
		if (!(*list)->value)
			cmd->cmd.cmd[i] = ft_strdup("");
		else
		{
			cmd->cmd.cmd[i] = ft_strdup((*list)->value);
			if (!cmd->cmd.cmd[i])
				return (printf(ALLOCATION_FAIL), 1);
		}
		cmd->cmd.cmd[i + 1] = NULL;
	}
	else
	{
		i = 0;
		while (cmd->cmd.cmd[i])
			i++;
		cmd->cmd.cmd = ft_realloc1(cmd->cmd.cmd, (i + 1) * sizeof(char *),
			(i + 2) * sizeof(char *));
		if (!(*list)->value)
			cmd->cmd.cmd[i] = ft_strdup("");
		else
		{
			cmd->cmd.cmd[i] = ft_strdup((*list)->value);
			if (!cmd->cmd.cmd[i])
				return (printf(ALLOCATION_FAIL), 1);
		}
		cmd->cmd.cmd[i + 1] = NULL;
	}
    *list = (*list)->next;
	return (0);
}
