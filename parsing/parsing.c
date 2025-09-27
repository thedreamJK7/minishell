/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/27 12:04:07 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_parse(t_token *token_list, int *exit_code)
{
	t_node	*nodes;

	nodes = parse_expression(&token_list, &(*exit_code));
	if (!nodes)
	{
		free_ast(nodes);
		return (NULL);
	}
	return (nodes);
}
