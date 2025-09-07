/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:50:04 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/05 13:21:57 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

// Errors
# define SYNTAX_ERROR1 "Syntax error: Invalid pipeline\n"
# define SYNTAX_ERROR2 "Syntax error: Invalid filename/limiter of redirection\n"

# define ALLOCATION_FAIL "Malloc error: Memory allocation fails\n"

# include "tokenizing.h"

typedef enum	e_node_type
{
	COMMAND,   // command (ls, grep, etc.)
	PIPE,       // pipe (|)
	REDIR      // redirection(<, >, <<, >>)
}				t_node_type;

typedef enum	e_redir_type
{
	IN,        // <
	OUT,       // >
	APPEND,    // >>
	HEREDOC    // <<
}	t_redir_type;

typedef struct	s_redir_token{
	t_redir_type	redir_type;// IN, OUT..
	char			*file;// Filename or limiter
	struct s_redir_token	*next;// token for redirection
}				t_redir_token;

typedef struct	s_command {
	char			**cmd;        // ["-l"], ["txt"], etc.
	t_redir_token	*redir_token;            // Redirection node if exists
}				t_command;

typedef struct	s_pipe {
	struct s_node	*left;   // left child (Command or Pipe)
	struct s_node	*right;  // right child (Command or Pipe)
}				t_pipe;

typedef struct	s_node {
	t_node_type	type;     // COMMAND, PIPE, REDIR
	union
	{
		struct	s_command cmd;  // Command Node uchun
		struct	s_pipe pipe;    // Pipe Node uchun
	};
}				t_node;


void			ft_parse(char **input);
void			print_ast(t_node *nodes, int depth); // Test
t_node 			*createNode(t_node_type type);
void			free_token_list(t_token *list);
void			free_redir_list(t_redir_token *list);
void			freeAST(t_node *node);
int				add_arg(t_node *cmd, t_token **list);
int				is_redirection(t_token_type type);
void			add_redir(t_node *cmd_node, t_redir_token *redir);
t_redir_token	*parseRedirection(t_token **list);
t_node			*parse_command(t_token **list);
t_node			*parse_expression(t_token **list);

#endif