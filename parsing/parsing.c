/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:46:47 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_parse(t_shell *shell, char *input)
{
	t_node	*nodes;
	t_token	*token_list;

	token_list = ft_tokenize(input, shell);
	if (!token_list)
		return (NULL);
	nodes = parse_expression(&token_list, &shell->exit_code);
	if (!nodes)
	{
		free_ast(nodes);
		return (NULL);
	}
	return (nodes);
}
