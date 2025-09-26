/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/26 14:41:28 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_arg(t_node *cmd, t_token **list)
{
	int 	i;

	i = 0;
	if (!cmd->cmd.cmd)
	{
		cmd->cmd.cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
		cmd->cmd.cmd[0] = ft_strdup((*list)->value);
		if (!cmd->cmd.cmd[i])
			return (printf(ALLOCATION_FAIL), 1);
		cmd->cmd.cmd[++i] = NULL;
	}
	else
	{
		i = 0;
		while (cmd->cmd.cmd[i])
			i++;
		cmd->cmd.cmd = ft_realloc1(cmd->cmd.cmd, (i + 1) * sizeof(char *), 
			(i + 2) * sizeof(char *));
		if (!(*list)->value)
			cmd->cmd.cmd[i] = NULL;
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
