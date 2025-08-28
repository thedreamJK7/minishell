/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:46:38 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/28 09:11:02 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*build_ast(t_token **list)
{
	t_node	*left_node;
	t_node	*pipe_node;

	if (!(*list) || (*list)->type == T_EOF)
		return (NULL);
	left_node = NULL;
	left_node = find_left(list);
	if (*list && (*list)->type == T_PIPE)
	{
		if ((*list)->next->type == T_PIPE)
		{
			printf(SYNTAX_ERROR1);
			free_ast(left_node);
			clean_tokens(list);
			exit(1);//cleanup memery
		}
		pipe_node = malloc(sizeof(t_node));
		if (!pipe_node)
			exit(1);//direct exit or return and exit in build_ast()?
		pipe_node->type = PIPE;
		pipe_node->pipe.left = left_node;
		*list = (*list)->next;
		pipe_node->pipe.right = build_ast(list);
		left_node = pipe_node;
	}
	return (left_node);
}
