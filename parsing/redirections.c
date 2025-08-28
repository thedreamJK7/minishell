/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:56:40 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/27 22:58:36 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*create_redir_node(t_token **list)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);//direct exit or return and exit in build_ast()?
	new_node->type = REDIR;
	if ((*list)->type == T_LESS)
		new_node->redir.redir_type = IN;
	else if ((*list)->type == T_GREAT)
		new_node->redir.redir_type = OUT;
	else if ((*list)->type == T_DGREAT)
		new_node->redir.redir_type = APPEND;
	else if ((*list)->type == T_DLESS)
		new_node->redir.redir_type = HEREDOC;
	*list = (*list)->next;
	if (*list && (*list)->type == T_WORD)
	{
		new_node->redir.file = ft_strdup((*list)->value);
		*list = (*list)->next;
	}
	else
	{
		printf(SYNTAX_ERROR2);
		free(new_node);
		exit(1);//cleanup memery
	}
	new_node->redir.child = NULL;
	return (new_node);
}
