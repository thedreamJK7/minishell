/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/26 17:29:36 by yingzhan         ###   ########.fr       */
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
		exit(1);//direct exit or return and exit in build_ast()?
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
		if ((*current_token)->type == T_LESS)
			new_node->redir.redir_type = IN;
		else if ((*current_token)->type == T_GREAT)
			new_node->redir.redir_type = OUT;
		else if ((*current_token)->type == T_DGREAT)
			new_node->redir.redir_type = APPEND;
		else if ((*current_token)->type == T_DLESS)
			new_node->redir.redir_type = HEREDOC;
		*current_token = (*current_token)->next;
		if (*current_token && (*current_token)->type == T_WORD)
		{
			new_node->redir.file = ft_strdup((*current_token)->value);
			*current_token = (*current_token)->next;
		}
		else
		{
			printf("Syntax error: Invalid filename/limiter of redirection");
			free(new_node);
			exit(1);
		}
		new_node->redir.child = NULL;
	}
	return (new_node);
}

t_node	*build_ast(t_token **list)
{
	t_node	*left_node;
	t_node	*pipe_node;
	t_node	*redir_node;

	left_node = NULL;
	while (*list && (*list)->type != T_EOF)
	{
		if ((*list)->type == T_WORD)
			left_node = create_node(COMMAND, list);
		else if ((*list)->type == T_LESS || (*list)->type == T_GREAT || (*list)->type == T_DLESS || (*list)->type == T_DGREAT)
		{
			redir_node = create_node(REDIR, list);
			if (!left_node && (*list)->type == T_WORD)
				left_node = create_node(COMMAND, list);
			redir_node->redir.child = left_node;
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

void	print_ast(t_node *nodes, int depth)
{
	int	i;

	if (!nodes)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("----");
		i++;
	}
	if (nodes->type == COMMAND)
	{
		printf("COMMAND: ");
		i = 0;
		while (nodes->cmd.args[i])
		{
			printf("%s ", nodes->cmd.args[i]);
			i++;
		}
		printf("\n");
	}
	else if (nodes->type == PIPE)
	{
		printf("PIPE: \n");
		print_ast(nodes->pipe.left, depth + 1);
		print_ast(nodes->pipe.right, depth + 1);
	}
	else if (nodes->type == REDIR)
	{
		printf("REDIR: ");
		if (nodes->redir.redir_type == 0)
			printf("< ");
		else if (nodes->redir.redir_type == 1)
			printf("> ");
		else if (nodes->redir.redir_type == 2)
			printf(">> ");
		else if (nodes->redir.redir_type == 3)
			printf("<< ");
		printf("Filename/Limiter: %s\n", nodes->redir.file);
		print_ast(nodes->redir.child, depth + 1);
	}
}
void	free_ast(t_node *nodes)
{
	int	i;

	if (!nodes)
		return ;
	if (nodes->type == COMMAND)
	{
		i = 0;
		while (nodes->cmd.args && nodes->cmd.args[i])
		{
			free(nodes->cmd.args[i]);
			i++;
		}
		free(nodes->cmd.args);
	}
	else if (nodes->type == PIPE)
	{
		free_ast(nodes->pipe.left);
		free_ast(nodes->pipe.right);
	}
	else if (nodes->type == REDIR)
	{
		free(nodes->redir.file);
		free_ast(nodes->redir.child);
	}
	free(nodes);
}

void	ft_parse(char *input)
{
	t_token	*token_list;
	t_token	*tmp_list;
	t_node	*nodes;

	token_list = ft_tokenize(input);
	tmp_list = token_list;
	nodes = build_ast(&tmp_list);
	print_ast(nodes, 0);//For test, should be removed later
//	execution;
	free_ast(nodes);
	clean_tokens(&token_list);
}
