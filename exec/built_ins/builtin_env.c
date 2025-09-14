/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:11:29 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/14 21:31:41 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_shell *shell, char **cmd)
{
	int	count;

	count = count_arguments(cmd);
	if (count == 1)
	{
		print_envp(shell->env_list);
		return (0);
	}
	printf("env: %s: No such file or directory", cmd[1]);
	return (1);
}
