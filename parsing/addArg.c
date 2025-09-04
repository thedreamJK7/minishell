/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addArg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 15:05:21 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_arg(t_node *cmd, t_token **list)
{
    t_token *cur;
	t_token *tmp;

	tmp = *list;
    
	if (!tmp)
		return (1);
	*list = tmp->next;
	tmp->next = NULL;
    if (!cmd->cmd.cmd_token)
        cmd->cmd.cmd_token = tmp;
    else
    {
        cur = cmd->cmd.cmd_token;
        while (cur->next)
            cur = cur->next;
        cur->next = tmp;
    }
	return (0);
}
