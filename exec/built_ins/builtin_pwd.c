/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:35:37 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:13:00 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* builtin_pwd function implements the 'pwd' builtin command.
	*
	* @param cmd: Command arguments (unused in this function).
	*
	* Behavior:
	* - Calls getcwd() to get the current working directory.
	* - If successful, prints the directory path to STDOUT.
	* - If getcwd() fails, prints an error message to STDERR.
	*
	* @return
	*   int → 0 on success, 1 on failure.
 */
int	builtin_pwd(char **cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 4096);
	if (cwd != NULL)
		return (printf("%s\n", cwd), free(cwd), 0);
	else
		return (perror("getcwd() error"), 1);
}
