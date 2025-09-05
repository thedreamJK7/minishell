/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/05 20:31:55 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse(char **input, t_shell *shell)
{
	t_token	*token_list;
	t_token	*tmp_list;
	t_node	*nodes;

	token_list = ft_tokenize(*input, shell);
	print_tokens(token_list);//print test for token list
	tmp_list = token_list;
	nodes = parse_expression(&tmp_list);
	if (!nodes)
	{
		freeAST(nodes);
		clean_tokens(&token_list, 0);
		return ;
	}
	print_ast(nodes, 1);// print test for ast node
	freeAST(nodes);
	clean_tokens(&token_list, 0);
}