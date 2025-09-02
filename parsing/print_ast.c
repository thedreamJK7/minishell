/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:31:07 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/02 15:12:29 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_ast(t_node *nodes, int depth)
{
	int	i;

	if (!nodes)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("----");
		i++;
	}
	if (nodes->type == COMMAND)
	{
		printf("COMMAND: ");
		i = 0;
		while (nodes->cmd.cmd_token)
		{
			printf("%s ", nodes->cmd.cmd_token->value);
			nodes->cmd.cmd_token = nodes->cmd.cmd_token->next;
		}
		printf("\n");
	}
	else if (nodes->type == PIPE)
	{
		printf("PIPE: \n");
		print_ast(nodes->pipe.left, depth + 1);
		print_ast(nodes->pipe.right, depth + 1);
	}
	else if (nodes->type == REDIR)
	{
		printf("REDIR: ");
		if (nodes->redir.redir_type == 0)
			printf("< ");
		else if (nodes->redir.redir_type == 1)
			printf("> ");
		else if (nodes->redir.redir_type == 2)
			printf(">> ");
		else if (nodes->redir.redir_type == 3)
			printf("<< ");
		printf("Filename/Limiter: %s\n", nodes->redir.file);
		print_ast(nodes->redir.child, depth + 1);
	}
}
