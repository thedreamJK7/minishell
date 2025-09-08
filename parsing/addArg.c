/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addArg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/08 14:27:43 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Fixing "" case

int	add_arg(t_node *cmd, t_token **list)
{
	int 	i;

	i = 0;
	if (!cmd->cmd.cmd)
	{
		cmd->cmd.cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
		if (!(*list)->value)
		{
			cmd->cmd.cmd[0] = ft_strdup("");
			if (cmd->cmd.cmd[0])
				return (printf(ALLOCATION_FAIL), 1);
		}
		else
		{
			cmd->cmd.cmd[0] = ft_strdup((*list)->value);
			if (!cmd->cmd.cmd[i])
				return (printf(ALLOCATION_FAIL), 1);
		}
		cmd->cmd.cmd[++i] = NULL;
	}
	else
	{
		i = 0;
		while (cmd->cmd.cmd[i])
			i++;
		cmd->cmd.cmd = ft_realloc1(cmd->cmd.cmd, i * sizeof(char *), 
			(i + 2) * sizeof(char *));
		if (!(*list)->value)
		{
			cmd->cmd.cmd[i] = ft_strdup("");
			if (!cmd->cmd.cmd[i])
				return (printf(ALLOCATION_FAIL), 1);
		}
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
