/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:24:18 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/15 10:48:09 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_first_char_valid(char c)
{
	return (('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c) || (c == '_'));
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

void	parse_export_arg(char *arg, char **name, char **value)
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
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
