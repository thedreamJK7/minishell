/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseRedirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:30:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 12:22:29 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int assignValue(t_redir_token **redir, t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (tmp->type == T_LESS)
		(*redir)->redir_type = IN;
	else if (tmp->type == T_GREAT)
		(*redir)->redir_type = OUT;
	else if (tmp->type == T_DGREAT)
		(*redir)->redir_type = APPEND;
	else if (tmp->type == T_DLESS)
		(*redir)->redir_type = HEREDOC;
	tmp = tmp->next;
	if (tmp && tmp->type == T_WORD)
	{
		(*redir)->file = tmp->value;
		tmp = tmp->next;
	}
	else
		return (printf(SYNTAX_ERROR2), free(*redir), 1);
	(*redir)->next = NULL;
	*list = tmp;
	return (0);
}

t_redir_token	*parseRedirection(t_token **list)
{
	t_redir_token	*redir;
	t_token	*tmp;

	tmp = *list;
	redir = malloc(sizeof(t_redir_token));
	if (!redir)
		return (printf(ALLOCATION_FAIL), NULL);
	if (assignValue(&redir, &tmp))
		return (NULL);
	*list = tmp;
	return (redir);
}
