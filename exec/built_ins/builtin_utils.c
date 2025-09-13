/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:01:55 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/13 11:36:56 by jkubaev          ###   ########.fr       */
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
