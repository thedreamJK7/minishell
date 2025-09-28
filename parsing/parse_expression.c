/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:35:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:25:58 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	validate_pipe_syntax(t_token *list, t_node *root, int *exit_code)
{
	if (!root || !list || list->type == T_PIPE || list->type == T_EOF)
	{
		*exit_code = 2;
		printf(SYNTAX_ERROR1);
		free_ast(root);
		return (1);
	}
	return (0);
}

static t_node	*create_pipe_node(t_node *left)
{
	t_node	*node;

	node = create_node(PIPE);
	if (!node)
		return (free_ast(left), NULL);
	node->pipe.left = left;
	return (node);
}

static int	parse_right_pipe_branch(t_node *pipe, t_token **list, 
	int *exit_code)
{
	pipe->pipe.right = parse_expression(list, exit_code);
	if (!(pipe->pipe.right))
	{
		free_ast(pipe->pipe.left);
		free(pipe);
		return (1);
	}
	return (0);
}

static t_node	*handle_the_pipe(t_node *root, t_token	**list, int *exit_code)
{
	t_node	*node;

	if (validate_pipe_syntax((*list)->next, root, exit_code))
		return (NULL);
	node = create_pipe_node(root);
	*list = (*list)->next;
	if (parse_right_pipe_branch(node, list, exit_code))
		return (NULL);
	return (node);
}

t_node	*parse_expression(t_token **list, int *exit_code)
{
	t_node	*root;

	root = NULL;
	if (*list && (*list)->type == T_EOF)
		return (NULL);
	if (*list && !((*list)->type == T_PIPE))
	{
		root = parse_command(list, exit_code);
		if (!root)
			return (NULL);
	}
	if (*list && (*list)->type == T_PIPE)
		root = handle_the_pipe(root, list, exit_code);
	return (root);
}
