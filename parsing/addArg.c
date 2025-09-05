/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addArg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 17:02:14 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_arg(t_node *cmd, t_token **list)
{
    t_token *cur;
    t_token *newArg;

	newArg = malloc(sizeof(t_token));
	if (!newArg)
		return (1);
	newArg->value = ft_strdup((*list)->value);
    if (!newArg->value)
        return (1);
    newArg->type = (*list)->type;
    newArg->next = NULL;
    if (!cmd->cmd.cmd_token)
        cmd->cmd.cmd_token = newArg;
    else
    {
        cur = cmd->cmd.cmd_token;
        while (cur->next)
            cur = cur->next;
        cur->next = newArg;
    }
    *list = (*list)->next;
	return (0);
}
