/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:03:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/24 12:26:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define GENERAL_ERROR 1
# define SYNTAX_ERROR 2
# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

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
	t_redir_token	*redir_token;
	int 			heredoc_fd;            // Redirection node if exists
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


typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env	*env_list;
	t_node	*nodes;
	char	*input;
	int		exit_code;
}				t_shell;



#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "../libft/includes/get_next_line.h"
#include "tokenizing.h"
#include "execution.h"
#include "parsing.h"

extern sig_atomic_t	g_sig_received;

void	setup_signals(void(*signal_handler)(int));
void	signal_handler_main(int sig);
void	signal_handler_exit(int sig);
void	signal_handler_wait(int sig);
void	free_env_list(t_env *envList);
void	clean_shell(t_shell	*shell);
t_shell	*init_envp(char **envp);
char	**envp_to_array(t_env *env_list);

#endif
