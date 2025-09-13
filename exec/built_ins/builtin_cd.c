/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:50:16 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/13 16:57:57 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arguments(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count);
}

int	builtin_cd(t_env *envp, char **cmd)
{
	int		argc;
	char	*pwd;
	char	*oldpwd;

	argc = count_arguments(cmd + 1);
	if (argc > 1)
		return (perror("minishell: cd: too many arguments"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd() error"), 1);
}