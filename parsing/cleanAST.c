/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanAST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:24:45 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 17:28:02 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_token_list(t_token *list)
{
    t_token	*tmp;

    while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->value) // malloc qilingan bo‘lsa
            free(tmp->value);
		free(tmp);
    }
}

void free_redir_list(t_redir_token *list)
{
    t_redir_token	*tmp;

    while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->file) // malloc qilingan bo‘lsa
            free(tmp->file);
		free(tmp);
    }
}

void	freeAST(t_node *node) 
{
    if (node == NULL)
		return ;
    if (node->type == COMMAND)
	{
		if (node->cmd.cmd_token)
			free_token_list(node->cmd.cmd_token);
		if (node->cmd.redir_token)
			free_redir_list(node->cmd.redir_token);
	}
	else if (node->type == PIPE) 
	{
        freeAST(node->pipe.left);
        freeAST(node->pipe.right);
    }
    free(node);
}
