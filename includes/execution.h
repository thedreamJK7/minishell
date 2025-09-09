/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:07:44 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/09 10:43:50 by yingzhan         ###   ########.fr       */
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
int	builtin_pwd(char **cmd);

#endif

