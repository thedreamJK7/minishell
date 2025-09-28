/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:35:37 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 18:17:38 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
