/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:56:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/11 18:43:54 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freeEnvList(t_env *envList)
{
	t_env	*tmp;

	while (envList)
	{
		tmp = envList;
		envList = envList->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	cleanShell(t_shell	*shell)
{
	freeEnvList(shell->env_list);
	free(shell);
}
