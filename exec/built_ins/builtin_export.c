/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:37:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/13 11:20:35 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_first_char_valid(char c)
{
	return ('a' >= c && 'z' >= c || 'A' >= c && 'Z' >= c || c == '_');
}

int	is_valid_identifier(char *name)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	if (!is_first_char_valid(name[i]))
		return (1);
	i++;
	while (name[i])
	{
		if (name[i] == '-')
		{
			valid = 1;
			break ;
		}
		if (name[i] == '=')
		{
			valid = 0;
			break ;
		}
		i++;
	}
	return (valid);
}

static void	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*name = ft_strdup(arg);
		*value = ft_strdup("");
	}
	else
	{
		*name = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
}

t_env	*is_env_exist(t_env *list, char *name)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	add_env(t_env *list, char *name, char *value)
{
	t_env *newList;
    t_env *current;

    newList = malloc(sizeof(t_env));
    if (!newList)
        return (1);
	newList->name = ft_strdup(name);
	newList->value = ft_strdup(value);
	newList->next = NULL;
    if (list == NULL) 
	{
        list = newList; 
        return (0);
    }
    current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newList;
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
		return (1);
	existing = is_env_exist(list, name);
	if (!existing)
		return (add_env(list, name, value));
	else
		return (update_env_value(existing, value));
}

int	builtin_export(t_env *list, char **cmd)
{
	int i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if (!cmd[i])
		return(print_env(list), 1);
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
		{
			printf("export: `%s': not a valid identifier", cmd[i]);
			exit_status = 1;	
		}
		else
			exit_status = update_or_add_env(list, cmd[i]);
		i++;
	}
	return (exit_status);
}
