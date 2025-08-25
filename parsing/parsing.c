/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/25 18:54:41 by yingzhan         ###   ########.fr       */
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
	add_tokens(&list, T_EOF, NULL);
//	print_tokens(list);//should be removed later
//	clean_tokens(&list);//should be used later
	return (list);
}

//	tokens to build an AST,

t_node	*create_node(t_node_type type, t_token **current_token)
{
	t_node	*new_node;
	t_token	*tmp;
	int i;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);
	new_node->type = type;
	if (type == COMMAND)
	{
		i = 0;
		tmp = *current_token;
		while (tmp && tmp->type == T_WORD)
		{
			i++;
			tmp = tmp->next;
		}
		new_node->cmd.args = malloc(sizeof(char *) * (i + 1));
		if (!new_node->cmd.args)
			exit(1);
		i = 0;
		while (*current_token && (*current_token)->type == T_WORD)
		{
			new_node->cmd.args[i++] = ft_strdup((*current_token)->value);
			// should be thinked to clean all the alocated memories, we need some functions for cleaning
			// should be checked allocation fails and if fails, free previous array elements
			*current_token = (*current_token)->next;
		}
		new_node->cmd.args[i] = NULL;
	}
	else if (type == REDIR)
	{
		if ((*current_token)->type == IN)
			new_node->cmd.redir.redir_type = 1;
		else if ((*current_token)->type == OUT)
			new_node->cmd.redir.redir_type = 2;
		else if ((*current_token)->type == APPEND)
			new_node->cmd.redir.redir_type = 3;
		else if ((*current_token)->type == HEREDOC)
			new_node->cmd.redir.redir_type = 4;
		*current_token = (*current_token)->next;
		if (*current_token && (*current_token)->type == T_WORD)
		{
			new_node->cmd.redir.file = ft_strdup((*current_token)->value);
			*current_token = (*current_token)->next;
		}
		else
		{
			printf("Syntax error: Invalid filename/limiter of redirection");
			free(new_node);
			exit(1);
		}
		new_node->cmd.redir.child = NULL;
	}
	return (new_node);
}

t_node	*build_ast(t_token **list)
{
	t_node	*left_node;
	t_node	*pipe_node;
	t_node	*redir_node;

	while (*list && (*list)->type != T_EOF)
	{
		if ((*list)->type == T_WORD)
			left_node = create_node(COMMAND, list);
		else if ((*list)->type == T_LESS || (*list)->type == T_GREAT || (*list)->type == T_DLESS || (*list)->type == T_DGREAT)
		{
			redir_node = create_node(REDIR, list);
			redir_node->cmd.redir.child = left_node;
			left_node = redir_node;
		}
		else if((*list)->type == T_PIPE)
		{
			pipe_node = create_node(PIPE, list);
			pipe_node->pipe.left = left_node;
			*list = (*list)->next;
			pipe_node->pipe.right = build_ast(list);
			left_node = pipe_node;
		}
	}
	return (left_node);
}

//print_ast
//free_ast

void	ft_parse(char *input)
{
	t_token	*token_list;
	t_token	*tmp_list;
	t_node	*nodes;

	token_list = ft_tokenize(input);
	tmp_list = token_list;
	nodes = build_ast(&tmp_list);
	print_ast(nodes, 0);
	free_ast(nodes);
	clean_tokens(token_list);
}
