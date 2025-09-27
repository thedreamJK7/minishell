/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:50:04 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/27 12:06:39 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

// Errors
# define SYNTAX_ERROR1 "Syntax error: Invalid pipeline\n"
# define SYNTAX_ERROR2 "Syntax error: Invalid filename/limiter of redirection\n"

# define ALLOCATION_FAIL "Malloc error: Memory allocation fails\n"

# include "minishell.h"
# include "tokenizing.h"

t_node			*ft_parse(t_token *token_list, int *exit_code);
void			print_ast(t_node *nodes, int depth); // Test
t_node 			*create_node(t_node_type type);
void			free_token_list(t_token *list);
void			free_redir_list(t_redir_token *list);
void			free_commands(char **argv);
void			free_ast(t_node *node);
int				add_arg(t_node *cmd, t_token **list);
int				is_redirection(t_token_type type);
void			add_redir(t_node *cmd_node, t_redir_token *redir);
t_redir_token	*parse_redirection(t_token **list, int *exit_code);
t_node			*parse_command(t_token **list, int *exit_code);
t_node			*parse_expression(t_token **list, int *exit_code);

#endif