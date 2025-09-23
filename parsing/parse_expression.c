/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:35:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/23 10:29:39 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_the_pipes(t_node **pipe, t_node **root, t_token	**list)
{
	if (!root || (*list)->next->type == T_PIPE
		|| (*list)->next->type == T_EOF)
		return (printf(SYNTAX_ERROR1), free_ast(*root), 1);
	(*pipe) = create_node(PIPE);
	if (!(*pipe))
		return (free_ast(*root), 1);
	(*pipe)->pipe.left = *root;
	(*list) = (*list)->next;
	(*pipe)->pipe.right = parse_expression(&(*list));
	if (!((*pipe)->pipe.right))
		return (free_ast((*pipe)->pipe.left), free(*pipe), 1);
	return (0);
}

t_node *parse_expression(t_token **list)
{
	t_node	*root;
	t_node	*pipe;
	t_token	*tmp;

	tmp = *list;
	root = NULL;
	pipe = NULL;
	if (tmp && tmp->type == T_EOF)
		return (NULL);
	if (tmp && !(tmp->type == T_PIPE))
	{
		root = parse_command(&tmp);
		if (!root)
			return (NULL);
	}
	if (tmp && tmp->type == T_PIPE)
	{
		if (handle_the_pipes(&pipe, &root, &tmp))
			return (NULL);
		root = pipe;
	}
	return (root);
}
