/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/12/01 23:28:19 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/*
 * ft_parse:
 *  Parses the input string into an abstract syntax tree (AST) of command nodes.
 *
 * Parameters:
 *  - shell: pointer to the shell structure containing environment and state
 *  - input: the raw command line input string
 *
 * Returns:
 *  - Pointer to the root node of the AST on success
 *  - NULL on failure
 *
 * Behavior:
 *  - Tokenizes the input string using ft_tokenize().
 *  - Parses the token list into a tree of command and pipe nodes using 
 * parse_expression().
 *  - Cleans up the token list to free memory.
 *  - If parsing fails, frees any partially created AST and returns NULL.
 *
 * Notes:
 *  - Updates shell->exit_code if any parsing errors occur.
 *  - Ensures no memory leaks by cleaning tokens and AST on failure.
 */
t_node	*ft_parse(t_shell *shell, char *input)
{
	t_node	*nodes;
	t_token	*token_list;

	token_list = ft_tokenize(input, shell);
	if (!token_list)
		return (NULL);
	nodes = parse_expression(&token_list, &shell->exit_code);
	clean_tokens(&token_list, 0);
	if (!nodes)
	{
		free_ast(nodes);
		return (NULL);
	}
	return (nodes);
}
