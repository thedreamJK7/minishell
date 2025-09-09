/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseExpression.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:35:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/08 17:45:46 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node *parse_expression(t_token **list)
{
	t_node	*root;
	t_node	*pipe;

	root = NULL;
	pipe = NULL;
	if ((*list) && (*list)->type == T_EOF)
		return (NULL);
	if ((*list) && ((*list)->type == T_WORD || is_redirection((*list)->type)))
	{
		root = parse_command(&(*list));
		if (!root)
			return (NULL);
	}
	if ((*list) && (*list)->type == PIPE)
	{
		if ((*list)->next->type == T_PIPE || (*list)->next->type == T_EOF)
			return (printf(SYNTAX_ERROR1), freeAST(root), NULL);
		pipe = createNode(PIPE);
		if (!pipe)
			return (freeAST(root), NULL);
		pipe->pipe.left = root;
		(*list) = (*list)->next;
		pipe->pipe.right = parse_expression(&(*list));
		if (!(pipe->pipe.right))
			return (freeAST(pipe->pipe.left), free(pipe), NULL);
		root = pipe;
	}
	return (root);
}
