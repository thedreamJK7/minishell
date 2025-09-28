/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:37:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 11:11:00 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env(char *name1, char *value)
{
	t_env *new_ist;

	new_ist = malloc(sizeof(t_env));
    if (!new_ist)
	{
        return (NULL);
	} 
	new_ist->name = ft_strdup(name1);
	if (!new_ist->name)
		return (free(new_ist), NULL);
	new_ist->value = ft_strdup(value);
	if (!new_ist->value)
		return (free(new_ist->name), free(new_ist), NULL);
	new_ist->next = NULL;
	return (new_ist);
}

int	add_env(t_env *list, char *name, char *value)
{
	t_env *new_list;
    t_env *current;

	new_list = create_env(name, value);
    if (list == NULL) 
	{
        list = new_list; 
        return (-1);
    }
    current = list;
    while (current->next != NULL)
        current = current->next;
    current->next = new_list;
	return (0);
}

static int	update_env_value(t_env *node, char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (1);
	free(node->value);
	node->value = new_value;
	return (0);
}

int	update_or_add_env(t_env *list, char	*idf)
{
	char *name;
	char *value;
	t_env	*existing;
	
	parse_export_arg(idf, &name, &value);
	if (!name || !value)
		return (-1);
	existing = is_env_exist(list, name);
	if (!existing)
		return (add_env(list, name, value));
	else
		return (update_env_value(existing, value));
}

int	builtin_export(t_shell *shell, char **cmd)
{
	int i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if (!cmd[i])
		return(print_envp(shell->env_list), 1);
	while (cmd[i])
	{
		if (is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else if (update_or_add_env(shell->env_list, cmd[i]) == -1)
			return (printf("Memory fail\n"), 1);
		i++;
	}
	return (exit_status);
}
