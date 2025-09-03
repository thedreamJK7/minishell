/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:50:04 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/02 16:30:26 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Errors
# define SYNTAX_ERROR1 "Syntax error: Invalid pipeline"
# define SYNTAX_ERROR2 "Syntax error: Invalid filename/limiter of redirection"

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

typedef struct	s_redir{
	t_redir_type	redir_type;// IN, OUT..
	char			*file;// Filename or limiter
	struct s_node	*child;// Node for redirection
}				t_redir;

typedef struct	s_command {
	t_token	*args;        // ["-l"], ["txt"], etc.
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
		struct	s_redir redir;  // Redirection
	};
}				t_node;

void	ft_parse(char *input);
void	free_ast(t_node *nodes);
void	print_ast(t_node *nodes, int depth);//should be removed later or better to keep it
t_node	*build_ast(t_token **list);
t_node	*find_left(t_token **list);
t_node	*create_redir_node(t_token **list);
t_node	*create_cmd_node(t_token **list, int empty);

#endif