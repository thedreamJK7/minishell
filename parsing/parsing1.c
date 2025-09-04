/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 12:42:42 by yingzhan         ###   ########.fr       */
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
	node->cmd.redir_token = NULL;
	node->cmd.cmd_token = NULL;
	return (node);
}
//ls -l | wc -l | sort

void free_token_list(t_token *list) {
    t_token	*tmp;

    while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp); // tmp->value ni free qilmaymiz, chunki u lexer tokenlariga ishora qiladi
    }
}

static void	freeAST(t_node *node)
{
    if (node == NULL)
		return ;
    if (node->type == COMMAND)
	{
		free_token_list(node->cmd.cmd_token);
		// if (node->cmd.redir)
		// 	freeAST(node->cmd.redir->child);
	}
	else if (node->type == PIPE)
	{
        freeAST(node->pipe.left);
        freeAST(node->pipe.right);
    }
    free(node);
}

void add_arg(t_node *cmd, t_token **list)
{
    t_token *new_arg;
    t_token *cur;

    new_arg = malloc(sizeof(t_token));
    if (!new_arg)
        return ;
    new_arg->value = (*list)->value;
	new_arg->type = (*list)->type;
    new_arg->next = NULL;
    if (!cmd->cmd.cmd_token) // agar list bo‘sh bo‘lsa
        cmd->cmd.cmd_token = new_arg;
    else
    {
        cur = cmd->cmd.cmd_token;
        while (cur->next)         // oxirigacha yurish
            cur = cur->next;
        cur->next = new_arg;      // yangi node qo‘shish
    }
}

int	is_redirection(t_token_type type)
{
	return (type == T_LESS || type == T_GREAT || type == T_DLESS
		|| type == T_DGREAT);
}

t_redir_token	*parseRedirection(t_token **list)
{
	t_redir_token	*redir;
	t_token	*tmp;

	tmp = *list;
	redir = malloc(sizeof(t_redir_token));
	if (!redir)
		return (NULL);
	if (tmp->type == T_LESS)
		redir->redir_type = IN;
	else if (tmp->type == T_GREAT)
		redir->redir_type = OUT;
	else if (tmp->type == T_DGREAT)
		redir->redir_type = APPEND;
	else if (tmp->type == T_DLESS)
		redir->redir_type = HEREDOC;
	tmp = tmp->next;
	if (tmp && tmp->type == T_WORD)
	{
		redir->file = tmp->value;
		tmp = tmp->next;
	}
	else
		return (printf(SYNTAX_ERROR2), free(redir), NULL);
	redir->next = NULL;
	*list = tmp;
	return (redir);
}

void	add_redir(t_node *cmd_node, t_redir_token *redir)
{
	t_redir_token *current;

	if (!cmd_node->cmd.redir_token)
		cmd_node->cmd.redir_token = redir;
	else
	{
		current = cmd_node->cmd.redir_token;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

t_node	*parse_command(t_token **list)
{
	t_node	*node;
	t_token	*tmp;
	t_redir_token	*redir;

	tmp = *list;
	node = createNode(COMMAND);
	if (!node)
		return (NULL);
	while (tmp && tmp->type != T_PIPE && tmp->type != T_EOF)
    {
        if (tmp->type == T_WORD || tmp->type == T_VAR)
        {
            add_arg(node, &tmp);
            tmp = tmp->next;
        }
        else if (is_redirection(tmp->type))
        {
            redir = parseRedirection(&tmp);
			if (!redir)
				return (freeAST(node), NULL);
            add_redir(node, redir);
        }
    }
	*list = tmp;
	return (node);
}


t_node *parse_expression(t_token **list)
{
	t_node	*root;
	t_node	*pipe;

	root = NULL;
	pipe = NULL;
	if ((*list) && (*list)->type == T_EOF)
		return (NULL);
	if ((*list) && ((*list)->type == T_WORD || is_redirection((*list)->type)))
	{
		root = parse_command(&(*list));
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
	print_tokens(token_list);
	tmp_list = token_list;
	nodes = parse_expression(&tmp_list);
	if (!nodes)
	{
		printf("returned null\n");
		clean_tokens(&token_list, 0);
		return ;
	}
//	print_ast(nodes, 0);
	print_exp(nodes);
	freeAST(nodes);
	clean_tokens(&token_list, 0);
}