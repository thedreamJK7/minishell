/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:12:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/19 13:10:10 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node(t_env **head, t_env *node_for_remove)
{
	t_env *tmp;
	t_env *previous;

	tmp = *head;
	if (tmp != NULL && tmp == node_for_remove)
    {
        *head = tmp->next;
		free(tmp->name);
		free(tmp->value);
        free(tmp);
        return ;
    }
	while (tmp != NULL && tmp != node_for_remove)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		previous->next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	builtin_unset(t_shell *shell, char **cmd)
{
	int		exit_status;
	int		i;
	t_env	*existing;

	exit_status = 0;
	i = 1;
	existing = NULL;
	while (cmd[i])
	{
		existing = is_env_exist(shell->env_list, cmd[i]);
		if (existing)
			remove_node(&(shell->env_list), existing);
		i++;
	}
	return (exit_status);
}
