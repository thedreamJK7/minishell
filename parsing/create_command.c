/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:12:38 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/28 09:23:28 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*create_cmd_node(t_token **list, int empty)
{
	t_node	*new_node;
	//t_redir	*redir;
	t_token	*tmp;
	int i;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);//direct exit or return and exit in build_ast()?
	new_node->type = COMMAND;
	if (empty)
	{
		new_node->cmd.args = malloc(sizeof(char *));
		if (!new_node->cmd.args)
			exit(1);//cleanup memery
		new_node->cmd.args[0] = NULL;
		return (new_node);
	}
	i = 0;
	tmp = *list;
	while (tmp && tmp->type == T_WORD)
	{
		i++;
		tmp = tmp->next;
	}
	new_node->cmd.args = malloc(sizeof(char *) * (i + 1));
	if (!new_node->cmd.args)
		exit(1);//cleanup memery
	i = 0;
	while (*list && (*list)->type == T_WORD)
	{
		new_node->cmd.args[i++] = ft_strdup((*list)->value);
		// should be thinked to clean all the alocated memories, we need some functions for cleaning
		// should be checked allocation fails and if fails, free previous array elements
		*list = (*list)->next;
	}
	new_node->cmd.args[i] = NULL;
	return (new_node);
}
