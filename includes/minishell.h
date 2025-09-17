/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:03:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/17 16:47:19 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define GENERAL_ERROR 1
# define SYNTAX_ERROR 2
# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env	*env_list;
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
#include "parsing.h"
#include "tokenizing.h"
#include "execution.h"

extern sig_atomic_t	g_sig_received;

void	setup_signals(void(*signal_handler)(int));
void	setup_signals_child(void);
void	signal_handler_main(int sig);
void	signal_handler_heredoc(int sig);
void	free_env_list(t_env *envList);
void	clean_shell(t_shell	*shell);
t_shell	*init_envp(char **envp);
char	**envp_to_array(t_env *env_list);

#endif
