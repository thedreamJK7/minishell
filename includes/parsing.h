/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:50:04 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/22 13:19:01 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_token_type
{
	T_WORD,//	normal word
	T_PIPE,//	|
	T_GREAT,//	>
	T_LESS, //	<
	T_DGREAT,//	>>
	T_DLESS,//	<<
	T_EOF//	end of file
}	t_token_type;

typedef	struct s_token
{
	t_token_type	type;
	char			*value; //command
	struct s_token	*next; // next node
}	t_token;

typedef enum	e_node_type
{
	COMMAND,   // command (ls, grep, etc.)
	PIPE       // pipe (|)
}				t_node_type;

typedef struct	s_command {
	char	*name;         // "ls", "grep", etc.
	char	**args;        // ["-l"], ["txt"], etc.
}				t_command;

typedef struct	s_pipe {
	struct s_node	*left;   // left child (Command or Pipe)
	struct s_node	*right;  // right child (Command or Pipe)
}				t_pipe;

typedef struct	s_node {
	t_node_type	type;     // COMMAND, PIPE
	union 
	{
		struct	s_command cmd;  // Command Node uchun
		struct	s_pipe pipe;    // Pipe Node uchun
	};
}				t_node;

// Functions
t_token	*ft_tokenize(char *s);

#endif