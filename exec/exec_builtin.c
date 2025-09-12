/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:08 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/12 14:37:47 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_shell *shell, char **cmd)
{
	int	bool;

	bool = 0;
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")))
		bool = builtin_pwd(cmd);
	if (!ft_strncmp(cmd[0], "export", ft_strlen("export")))
		bool = builtin_pwd(cmd);
	return (bool);
}
