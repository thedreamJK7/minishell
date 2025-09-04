/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addArg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 11:28:16 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_arg(t_node *cmd, t_token **list)
{
    t_token *new_arg;
    t_token *cur;

    new_arg = malloc(sizeof(t_token));
    if (!new_arg)
        return (1);
    new_arg->value = (*list)->value;
	new_arg->type = (*list)->type;
    new_arg->next = NULL;
    if (!cmd->cmd.cmd_token)
        cmd->cmd.cmd_token = new_arg;
    else
    {
        cur = cmd->cmd.cmd_token;
        while (cur->next)
            cur = cur->next;
        cur->next = new_arg;
    }
	return (0);
}
