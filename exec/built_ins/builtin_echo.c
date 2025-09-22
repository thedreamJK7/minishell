/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:51:30 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/20 12:51:34 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_shell *shell, char **cmd)
{
	int i;

	i = 1;
	if (cmd[i] && !ft_strcmp(cmd[i], "-n"))
	{
		i++;
		while (cmd[i] && (cmd[i + 1] != NULL))
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("%s", cmd[i]);
	}
	else
	{
		while (cmd[i] && (cmd[i + 1] != NULL))
		{
			printf("%s ", cmd[i]);
			i++;
		}
		if (cmd[i])
			printf("%s\n", cmd[i]);
		else
			write(1, "\n", 1);
	}
	shell->exit_code = 0;
	return (0);
}
