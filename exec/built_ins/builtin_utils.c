/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:01:55 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/14 13:04:32 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_envp(t_env *shell)
{
	t_env	*current;

	current = shell;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;	
	}
}

int	count_arguments(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count);
}
