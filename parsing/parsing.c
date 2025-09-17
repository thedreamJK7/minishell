/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/16 15:47:16 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_parse(char **input, t_shell *shell)
{
	t_token	*token_list;
	t_node	*nodes;

	token_list = ft_tokenize(*input, shell);
	if (!token_list)
		return (NULL);
	nodes = parse_expression(&token_list);
	if (!nodes)
	{
		free_ast(nodes);
		clean_tokens(&token_list, 0);
		return (NULL);
	}
	clean_tokens(&token_list, 0);
	return (nodes);
}
