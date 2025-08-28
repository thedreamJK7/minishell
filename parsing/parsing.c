/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/28 09:37:56 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	// <<1 <<2 rev>outline
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
		else if ((*list)->type == T_LESS || (*list)->type == T_GREAT ||
			(*list)->type == T_DLESS || (*list)->type == T_DGREAT)
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
