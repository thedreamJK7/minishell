/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/25 12:44:53 by jkubaev          ###   ########.fr       */
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

//	redirections
t_redir	*collect_redirections(t_token **current_token)
{
	t_token	*tmp;
	t_redir	*prev_redir;
	t_redir	*current_redir;
	
	prev_redir = malloc(sizeof(t_redir));
	tmp = *current_token;
	if (tmp->type == T_GREAT)
		prev_redir->redir_type = OUT;
	if (tmp->type == T_LESS)
		prev_redir->redir_type = IN;
	if (tmp->type == T_DGREAT)
		prev_redir->redir_type = APPEND;
	if (tmp->type == T_DLESS)
		prev_redir->redir_type = HEREDOC;
	tmp = tmp->next;
	if (tmp->next != T_WORD)
		exit(1);
	if (tmp->type != T_PIPE && tmp->type != T_EOF)
	{
		
	}
	*current_token = tmp;
	return (tmp);
}

//	tokens to build an AST,

t_node	*create_node(t_node_type type, t_token **current_token)
{
	t_node	*new_node;
	t_redir	*redir;
	t_token	*tmp;
	int i;

	tmp = *current_token;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);
	new_node->type = type;
	if (type == COMMAND)
	{
		i = 0;
		new_node->cmd.name = ft_strdup(tmp->value);
		tmp = tmp->next;
		new_node->cmd.args = malloc(sizeof(char **) * (i + 1));
		if (!new_node->cmd.args)
			exit(1);
		while (tmp->type != T_PIPE && tmp->type != T_EOF)
		{
			if (tmp->type == T_DGREAT || tmp->type == T_LESS ||
				tmp->type == T_GREAT || tmp->type == T_DLESS)
			{
				
			}
			else
			{
				new_node->cmd.args[i++] = ft_strdup(tmp->value);
				// should be thinked to clean all the alocated memories, we need some functions for cleaning
				new_node->cmd.args = realloc(new_node->cmd.args, i + 1);
				// should be checked allocation fails and if fails, free previous array elements	
				tmp = tmp->next;
			}
		}
		new_node->cmd.args[i] = NULL;
	}
	*current_token = tmp;
	return (new_node);
}

t_node	*build_ast(t_token *list)
{
	t_node	*prev_node;
	t_node	*current_node;

	while (list->type != T_EOF)
	{
		if (list->type == T_WORD)
			prev_node = create_node(COMMAND, &list);
		if(list->type == T_PIPE)
		{
			current_node = create_node(PIPE, &list);
			current_node->pipe.left = prev_node;
			prev_node->pipe.right = build_ast(list->next);
		}
	}
	return (current_node);
}

void	ft_parse(char *input)
{
	t_token	*token_list;
	t_node	*nodes;

	token_list = ft_tokenize(input);
	nodes = build_ast(token_list);
}
