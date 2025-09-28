/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:30:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:26:19 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_redir_type(t_redir_token *redir, t_token *list)
{
	if (list->type == T_LESS)
		redir->redir_type = IN;
	else if (list->type == T_GREAT)
		redir->redir_type = OUT;
	else if (list->type == T_DGREAT)
		redir->redir_type = APPEND;
	else if (list->type == T_DLESS)
		redir->redir_type = HEREDOC;
}

static int	assign_value(t_redir_token **redir, t_token **list, int *exit_code)
{
	set_redir_type(*redir, *list);
	(*list) = (*list)->next;
	if ((*list) && (*list)->type == T_WORD)
	{
		(*redir)->file = ft_strdup((*list)->value);
		if (!(*redir)->file)
			return (printf(ALLOCATION_FAIL), free(*redir), 1);
		(*list) = (*list)->next;
	}
	else
	{
		*exit_code = 2;
		return (printf(SYNTAX_ERROR2), free(*redir), 1);
	}
	(*redir)->next = NULL;
	return (0);
}

t_redir_token	*parse_redirection(t_token **list, int *exit_code)
{
	t_redir_token	*redir;
	t_token			*tmp;

	tmp = *list;
	redir = malloc(sizeof(t_redir_token));
	if (!redir)
		return (printf(ALLOCATION_FAIL), NULL);
	if (assign_value(&redir, &tmp, &(*exit_code)))
		return (NULL);
	*list = tmp;
	return (redir);
}
