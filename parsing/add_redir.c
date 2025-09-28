/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:31:54 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:24:44 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir(t_node *cmd_node, t_redir_token *redir)
{
	t_redir_token	*current;

	if (!cmd_node->cmd.redir_token)
		cmd_node->cmd.redir_token = redir;
	else
	{
		current = cmd_node->cmd.redir_token;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}
