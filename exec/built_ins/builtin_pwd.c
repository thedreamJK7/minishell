/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:35:37 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/08 18:47:23 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_arguments_valid(char **cmd)
{
	int	arg;

	arg = 0;
	while (*cmd)
	{
		cmd++;
		arg++;
	}
	if (arg == 1)
		return (0);
	else
		return (1);
}

int	builtin_pwd(char **cmd)
{
	char *cwd;
	if (is_arguments_valid(cmd))
		return(printf("pwd: too many arguments\n"), 1);
	cwd = getcwd(NULL, 0);
	if ( cwd != NULL)
		return (printf("%s\n", cwd), free(cwd), 0);
	else
		return (perror("getcwd() error"), 1);
}
