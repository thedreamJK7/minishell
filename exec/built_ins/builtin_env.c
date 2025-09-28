/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:11:29 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 10:53:16 by jkubaev          ###   ########.fr       */
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
	fprintf(stderr, "env: %s: No such file or directory\n", cmd[1]);
	return (127);
}
