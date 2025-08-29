/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:56:40 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/29 12:07:45 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*create_redir_node(t_token **list)
{
	t_node	*new_node;
	t_token	*tmp;

	tmp = *list;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);//direct exit or return and exit in build_ast()?
	new_node->type = REDIR;
	if (tmp->type == T_LESS)
		new_node->redir.redir_type = IN;
	else if (tmp->type == T_GREAT)
		new_node->redir.redir_type = OUT;
	else if (tmp->type == T_DGREAT)
		new_node->redir.redir_type = APPEND;
	else if (tmp->type == T_DLESS)
		new_node->redir.redir_type = HEREDOC;
	tmp = tmp->next;
	if (tmp && tmp->type == T_WORD)
	{
		new_node->redir.file = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	else
	{
		printf(SYNTAX_ERROR2);
		free(new_node);
		return (NULL);
		//exit(1);//cleanup memery
	}
	new_node->redir.child = NULL;
	*list = tmp;
	return (new_node);
}
