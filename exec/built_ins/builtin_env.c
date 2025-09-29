/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:11:29 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 09:53:31 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* builtin_env function implements the 'env' builtin command.
	*
	* @param shell: Pointer to the main shell structure --
	* containing environment variables.
	* @param cmd:   Array of command arguments (e.g., ["env", ...]).
	*
	* Behavior:
	* - If called without extra arguments, prints all environment variables.
	* - If called with additional arguments, prints an error message:
	*   "env: <argument>: No such file or directory".
	*
	* @return 0 on success (only 'env' command),
	*         127 when an invalid argument is provided.
 */
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
