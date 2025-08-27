/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/27 17:03:33 by yingzhan         ###   ########.fr       */
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

t_node	*create_cmd_node(t_token **list, int empty)
{
	t_node	*new_node;
	t_token	*tmp;
	int i;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);//direct exit or return and exit in build_ast()?
	new_node->type = COMMAND;
	if (empty)
	{
		new_node->cmd.args = malloc(sizeof(char *));
		if (!new_node)
			exit(1);//cleanup memery
		new_node->cmd.args[0] = NULL;
		return (new_node);
	}
	i = 0;
	tmp = *list;
	while (tmp && tmp->type == T_WORD)
	{
		i++;
		tmp = tmp->next;
	}
	new_node->cmd.args = malloc(sizeof(char *) * (i + 1));
	if (!new_node->cmd.args)
		exit(1);//cleanup memery
	i = 0;
	while (*list && (*list)->type == T_WORD)
	{
		new_node->cmd.args[i++] = ft_strdup((*list)->value);
		// should be thinked to clean all the alocated memories, we need some functions for cleaning
		// should be checked allocation fails and if fails, free previous array elements
		*list = (*list)->next;
	}
	new_node->cmd.args[i] = NULL;
	return (new_node);
}

t_node	*create_redir_node(t_token **list)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);//direct exit or return and exit in build_ast()?
	new_node->type = REDIR;
	if ((*list)->type == T_LESS)
		new_node->redir.redir_type = IN;
	else if ((*list)->type == T_GREAT)
		new_node->redir.redir_type = OUT;
	else if ((*list)->type == T_DGREAT)
		new_node->redir.redir_type = APPEND;
	else if ((*list)->type == T_DLESS)
		new_node->redir.redir_type = HEREDOC;
	*list = (*list)->next;
	if (*list && (*list)->type == T_WORD)
	{
		new_node->redir.file = ft_strdup((*list)->value);
		*list = (*list)->next;
	}
	else
	{
		printf("Syntax error: Invalid filename/limiter of redirection");
		free(new_node);
		exit(1);//cleanup memery
	}
	new_node->redir.child = NULL;
	return (new_node);
}

void	add_cmd_args(t_node *cmd_node, t_token **list)
{
	int		i;
	int		j;
	char	**new_array;
	char	*value;

	i = 0;
	while (cmd_node->cmd.args && cmd_node->cmd.args[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		exit(1);//cleanup memery
	j = 0;
	while (j < i)
	{
		new_array[j] = cmd_node->cmd.args[j];
		j++;
	}
	value = ft_strdup((*list)->value);
	if (!value)
		exit(1);//cleanup memory
	new_array[i] = value;
	new_array[i + 1] = NULL;
	free(cmd_node->cmd.args);
	cmd_node->cmd.args = new_array;
	*list = (*list)->next;
}
//cmd_node is always created at the beginning, even if there is no cmd
t_node	*find_left(t_token **list)
{
	t_node	*cmd_node;
	t_node	*redir_node;
	t_node	*last_redir;

	cmd_node = NULL;
	redir_node = NULL;
	last_redir = NULL;
	while (*list && (*list)->type != T_EOF && (*list)->type != T_PIPE)
	{
		if ((*list)->type == T_WORD)
		{
			if (!cmd_node)
				cmd_node = create_cmd_node(list, 0);
			else
				add_cmd_args(cmd_node, list);
		}
		else if ((*list)->type == T_LESS || (*list)->type == T_GREAT || (*list)->type == T_DLESS || (*list)->type == T_DGREAT)
		{
			redir_node = create_redir_node(list);
			if (!cmd_node)
				cmd_node = create_cmd_node(list, 1);
			if (last_redir)
				redir_node->redir.child = last_redir;
			else
				redir_node->redir.child = cmd_node;
			last_redir = redir_node;
		}
	}
	if (last_redir)
		return (last_redir);
	else
		return (cmd_node);
}

t_node	*build_ast(t_token **list)
{
	t_node	*left_node;
	t_node	*pipe_node;

	if (!(*list) || (*list)->type == T_EOF)
		return (NULL);
	left_node = NULL;
	left_node = find_left(list);
	if (*list && (*list)->type == T_PIPE)
	{
		if ((*list)->next->type == T_PIPE)
		{
			printf("Syntax error: Invalid pipeline");
			free_ast(left_node);
			clean_tokens(list);
			exit(1);//cleanup memery
		}
		pipe_node = malloc(sizeof(t_node));
		if (!pipe_node)
			exit(1);//direct exit or return and exit in build_ast()?
		pipe_node->type = PIPE;
		pipe_node->pipe.left = left_node;
		*list = (*list)->next;
		pipe_node->pipe.right = build_ast(list);
		left_node = pipe_node;
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
