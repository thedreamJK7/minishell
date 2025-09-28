/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:31:07 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/28 12:52:50 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_ast(t_node *nodes, int depth)
{
	int	i;
	int j;

//	if (!nodes)
//		return ;
	i = 0;
	while (i < depth)
	{
		printf("----");
		i++;
	}
	if (nodes->type == COMMAND)
	{
		printf("COMMAND: ");
		j = 0;
		while (nodes->cmd.cmd[j])
		{
			printf("%s ", nodes->cmd.cmd[j]);
			j++;
		}
		printf("\n");
		i = 0;
		while (i < depth)
		{
			printf("----");
			i++;
		}
		printf("REDIR: ");
		if (!nodes->cmd.redir_token)
		{
			printf("Empty");
		}
		else
		{
			while (nodes->cmd.redir_token)
			{
				printf("%i %s ", nodes->cmd.redir_token->redir_type, nodes->cmd.redir_token->file);
				nodes->cmd.redir_token = nodes->cmd.redir_token->next;
			}
		}
		printf("\n");
	}
	else if (nodes->type == PIPE)
	{
		printf("PIPE: \n");
		print_ast(nodes->pipe.left, depth + 1);
		print_ast(nodes->pipe.right, depth + 1);
	}
}
