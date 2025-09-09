/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:07:44 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/09 11:18:04 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing.h"
# include <sys/types.h>
# include <sys/wait.h>

int	execute(t_node *node, t_shell *shell);
int	exec_pipe(t_node *pipe_node, t_shell *shell);
int	exec_builtin(char **cmd);
int	exec_non_builtin(t_node *cmd, t_shell *shell);
int	builtin_pwd(char **cmd);

#endif

