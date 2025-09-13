/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:07:44 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/13 11:23:57 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

int		execute(t_node *node, t_shell *shell);
int		exec_pipe(t_node *pipe_node, t_shell *shell);
int		exec_builtin(char **cmd);
int		exec_non_builtin(t_node *cmd, t_shell *shell);
int		handle_heredoc(t_redir_token *redir, int *in_fd);
void	clean_array(char **arr);
void	close_fd(int in_fd, int out_fd);
int		check_access(char *path);
int		builtin_pwd(char **cmd);
int		builtin_export(t_shell *shell, char	**cmd);

#endif

