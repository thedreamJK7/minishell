/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:34:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/27 20:52:15 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == T_LESS || type == T_GREAT || type == T_DLESS 
		|| type == T_DGREAT);
}

t_node	*parse_command(t_token **list, int *exit_code)
{
	t_node	*node;
	t_redir_token	*redir;

	node = create_node(COMMAND);
	if (!node)
		return (NULL);
	while ((*list) && (*list)->type != T_PIPE && (*list)->type != T_EOF)
    {
		while ((*list)->type == T_WORD && 
			(*list)->value && ((*list)->value[0] == 0))
			(*list) = (*list)->next;
		if ((*list)->type == T_WORD)
        {
            if (add_arg(node, &(*list)))
				return (free_ast(node), NULL);
        }
        else if (is_redirection((*list)->type))
        {
            redir = parse_redirection(&(*list), &(*exit_code));
			if (!redir)
				return (free_ast(node), NULL);
			add_redir(node, redir);
        }
    }
	return (node);
}
