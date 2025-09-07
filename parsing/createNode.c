/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createNode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:23:34 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/05 13:22:11 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node *createNode(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (printf(ALLOCATION_FAIL), NULL);
	node->type = type;
	node->pipe.left = NULL;
	node->pipe.right = NULL;
	node->cmd.redir_token = NULL;
	node->cmd.cmd = NULL;
	return (node);
}