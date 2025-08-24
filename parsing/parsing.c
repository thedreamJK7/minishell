/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/24 11:59:00 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_tokenize(char *s)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (!s[i])
			break ;
		if (ft_strchr("|><", s[i]) && s[i + 1] && s[i + 1] == s[i])
			i += specify_tokens(s[i], &list, 0);
		else if (ft_strchr("|><", s[i]) && !(s[i + 1] && s[i + 1] == s[i]))
			i += specify_tokens(s[i], &list, 1);
		else if (ft_strchr("'\"", s[i]))
			i += handle_quotes(s + i, s[i], &list);
		else
			i += handle_words(s + i, &list);
	}
//	print_tokens(list);//should be removed later
//	clean_tokens(&list);//should be used later
	return (list);
}

//	tokens to build an AST,

void	build_ast(t_token *list, t_node *node)
{
	while (list->type != T_EOF)
	{
		if (list->type == T_WORD)
		{
			node->type = list->type;
			node->cmd.name = T_WORD;
		}
		else if(list->type == T_PIPE)
		{
			build_ast(list->next, node->next);
		}
		list = list->next;
	}
}

void	ft_parse(char *input)
{
	t_token	*token_list;

	token_list = ft_tokenize(input);
}
