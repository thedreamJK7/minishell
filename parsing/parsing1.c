/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/02 11:06:53 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_node *createNode(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->pipe.left = NULL;
	node->pipe.right = NULL;
	node->redir.file = NULL;
	node->redir.child = NULL;
	return (node);
}

t_node	*parse_command(t_token **list)
{
	t_node	*node;
	t_token	*tmp;
	int		i;

	node = createNode(COMMAND);
	if (!node)
		return (NULL);
	tmp = *list;
	i = 0;
	while (tmp->type == T_WORD)
	{
		i++;
		tmp = tmp->next;
	}
	node->cmd.args = (char **)malloc(sizeof(char *) * (i + 1));
	if (node->cmd.args == NULL)
        return (free(node), NULL);
	i = 0;
	tmp = *list;
	while (tmp->type == T_WORD)
	{
		node->cmd.args[i++] = tmp->value;
		tmp = tmp->next;
	}
	*list = tmp;
	return (node);
}

t_node	*parseRedirection(t_token **list)
{
	t_node	*node;
	t_token	*tmp;

	tmp = *list;
	node = createNode(REDIR);
	if (!node)
		return (NULL);
	if (tmp->type == T_LESS)
		node->redir.redir_type = IN;
	else if (tmp->type == T_GREAT)
		node->redir.redir_type = OUT;
	else if (tmp->type == T_DGREAT)
		node->redir.redir_type = APPEND;
	else if (tmp->type == T_DLESS)
		node->redir.redir_type = HEREDOC;
	tmp = tmp->next;
	if (tmp && tmp->type == T_WORD)
	{
		node->redir.file = tmp->value;
		tmp = tmp->next;
	}
	else
		return(printf(SYNTAX_ERROR2), free(node), NULL);
	*list = tmp;
	return (node);
}

static void	freeAST(t_node *node) 
{
    if (node == NULL) 
		return ;
    if (node->type == COMMAND)
		free(node->cmd.args);
	else if (node->type == PIPE) 
	{
        freeAST(node->pipe.left);
        freeAST(node->pipe.right);
    } else if (node->type == REDIR)
	{
        //freeAST(node->redir.cmd);
		freeAST(node->redir.child);
    }
    free(node);
}

t_node *parse_expression(t_token **list)
{
	t_node	*root;
	t_node	*pipe;

	root = NULL;
	pipe = NULL;
	if ((*list) && (*list)->type == T_EOF)
		return (NULL);
	if ((*list) && (*list)->type == T_WORD)
	{
		root = parse_command(&(*list));
		if (!root)
			return (NULL);
	}
	if ((*list) && ((*list)->type == T_DGREAT || (*list)->type == T_DLESS ||
		(*list)->type == T_GREAT || (*list)->type == T_LESS))
	{
		root = parseRedirection(&(*list));
		if (!root)
			return (NULL);
	}
	if ((*list) && (*list)->type == PIPE)
	{
		if ((*list)->next->type == T_PIPE)
			return (printf(SYNTAX_ERROR1), freeAST(root), NULL);
		pipe = createNode(PIPE);
		if (!pipe)
			return (freeAST(root), NULL);
		pipe->pipe.left = root;
		(*list) = (*list)->next;
		pipe->pipe.right = parse_expression(&(*list));
		if (!(pipe->pipe.right))
			return (freeAST(pipe->pipe.left), free(pipe), NULL);
		root = pipe;
	}
	return (root);
}


void	ft_parse(char **input)
{
	t_token	*token_list;
	t_token	*tmp_list;
	t_node	*nodes;

	token_list = ft_tokenize(*input);
	tmp_list = token_list;
	//print_tokens(tmp_list);
	nodes = parse_expression(&tmp_list);
	if (!nodes)
	{
		printf("returned null\n");
		freeAST(nodes);
		clean_tokens(&token_list);
		return ;
	}
	print_ast(nodes, 0);
	freeAST(nodes);
	clean_tokens(&token_list);
}