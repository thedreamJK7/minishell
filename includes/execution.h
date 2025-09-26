/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/09/26 14:22:41 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

int		execute(t_node *node, t_shell *shell);
int		exec_pipe(t_node *pipe_node, t_shell *shell);
int		exec_builtin(t_shell *shell, char **cmd);
int		exec_non_builtin(t_node *cmd, t_shell *shell);
int		exec_heredoc(t_redir_token *redir, t_shell *shell, int *in_fd);
void	find_heredoc(t_node *node, t_shell *shell);
void	clean_array(char **arr);
void	close_fd(int in_fd, int out_fd);
void	close_heredoc_fd(t_node *node);
int		check_access(char *path);
int		check_dir(char *path, int *flag);
int		print_error_cmd(int flag, char *cmd_name);
int		print_error_path(int flag, char *cmd_name);
int		builtin_pwd(char **cmd);
int		builtin_export(t_shell *shell, char **cmd);
void	print_envp(t_env *envp);
int		is_valid_identifier(char *name);
void	parse_export_arg(char *arg, char **name, char **value);
t_env	*is_env_exist(t_env *list, char *name);
int		builtin_cd(t_shell *shell, char **cmd);
int		count_arguments(char **cmd);
int		builtin_exit(t_shell *shell, char **cmd);
int		builtin_env(t_shell *shell, char **cmd);
int		builtin_unset(t_shell *shell, char **cmd);
char	*exp_heredoc(char *input, t_shell *shell);
int		builtin_echo(t_shell *shell, char **cmd);

#endif

