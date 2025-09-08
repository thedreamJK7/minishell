/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:34:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/08 12:35:13 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*parse_command(t_token **list)
{
	t_node	*node;
	t_token	*tmp;
	t_redir_token	*redir;

	tmp = *list;
	node = createNode(COMMAND);
	if (!node)
		return (NULL);
	while (tmp && tmp->type != T_PIPE && tmp->type != T_EOF)
    {
        if (tmp->type == T_WORD)
        {
            if (add_arg(node, &tmp))
				return (freeAST(node), NULL);
        }
        else if (is_redirection(tmp->type))
        {
            redir = parseRedirection(&tmp);
			if (!redir)
				return (freeAST(node), NULL);
            add_redir(node, redir);
        }
    }
	*list = tmp;
	return (node);
}
