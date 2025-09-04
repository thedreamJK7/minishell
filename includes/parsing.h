/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/04 12:05:56 by yingzhan         ###   ########.fr       */
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

//ls > output.txt -l >>1
typedef struct	s_redir_token{
	t_redir_type	redir_type;// IN, OUT..
	//t_command		cmd;
	char			*file;// Filename or limiter
	struct s_redir_token	*next;// token for redirection
}				t_redir_token;

typedef struct	s_command {
	t_token			*cmd_token;        // ["-l"], ["txt"], etc.
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


void	ft_parse(char **input);
//void	free_ast(t_node *nodes);
void	print_ast(t_node *nodes, int depth);//should be removed later or better to keep it
// t_node	*build_ast(t_token **list);
// t_node	*find_left(t_token **list);
// t_node	*create_redir_node(t_token **list);
// t_node	*create_cmd_node(t_token **list, int empty);

#endif