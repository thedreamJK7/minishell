/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:24:45 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/24 17:13:55 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_commands(char **argv)
{
	int i;

	if (!argv)
		return ;
	i = 0;
    while (argv[i])
	{
		free(argv[i]);
		i++;
    }
	free(argv);
}

void free_redir_list(t_redir_token *list)
{
    t_redir_token	*tmp;

    while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->file)
            free(tmp->file);
		free(tmp);
    }
}

void	free_ast(t_node *node)
{
    if (node == NULL)
		return ;
    if (node->type == COMMAND)
	{
		if (node->cmd.cmd)
			free_commands(node->cmd.cmd);
		if (node->cmd.redir_token)
			free_redir_list(node->cmd.redir_token);
		if (node->cmd.heredoc_fd)
			close_heredoc_fd(&node->cmd);
	}
	else if (node->type == PIPE)
	{
        free_ast(node->pipe.left);
        free_ast(node->pipe.right);
    }
    free(node);
}
