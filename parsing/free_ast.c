/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:29:18 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/28 17:30:27 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ast(t_node *nodes)
{
	int	i;

	if (!nodes)
		return ;
	if (nodes->type == COMMAND)
	{
		i = 0;
		while (nodes->cmd.args && nodes->cmd.args[i])
		{
			free(nodes->cmd.args[i]);
			i++;
		}
		free(nodes->cmd.args);
	}
	else if (nodes->type == PIPE)
	{
		free_ast(nodes->pipe.left);
		free_ast(nodes->pipe.right);
	}
	else if (nodes->type == REDIR)
	{
		free(nodes->redir.file);
		free_ast(nodes->redir.child);
	}
	free(nodes);
}
