/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:58:36 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/14 15:11:11 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_exit_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (-1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		i++;
	}
	return (-1);
}

static int	handle_exit_args(char *arg)
{
	int		exit_code;

	exit_code = validate_exit_arg(arg);
	if (exit_code != -1)
		return (exit_code);
	exit_code = ft_atoi(arg);
	return (exit_code);
}

int	builtin_exit(t_shell *shell, char **cmd)
{
	int	count;
	int	exit_code;

	count = count_arguments(cmd);
	exit_code = shell->exit_code;
	if (count > 3)
		return (printf("exit: too many arguments\n"), 1);
	else
	{
		exit_code = handle_exit_args(*(cmd + 1));
		if (exit_code == -1)
			return (1);
	}
	clean_shell(shell);
	exit(exit_code);
}