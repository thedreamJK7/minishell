/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:37:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/12 17:39:11 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

MY_VAR=hello	✅ Valid	The variable name uses valid 
				characters (letters and underscore).

my-var=hello	❌ Invalid	The hyphen - is not a 
				valid character for a variable name.

1VAR=hello		❌ Invalid	A variable name cannot start with a digit.

_VAR=hello		✅ Valid	A variable name can start with an underscore _.

VAR=hello world	✅ Valid	This is valid if the quotes 
				were handled correctly during parsing.

export (no arguments)	✅ Valid	When no arguments are 
						given, export prints all environment variables.
*/

int	is_first_char_valid(char c)
{
	return ('a' >= c && 'z' >= c || 'A' >= c && 'Z' >= c || c == '_');
}

int	is_valid_identifier(char *idf)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	if (!is_first_char_valid(idf[i]))
		return (1);
	i++;
	while (idf[i])
	{
		if (idf[i] == '-')
		{
			valid = 1;
			break ;
		}
		else if (idf[i] == '=')
		{
			valid = 0;
			break ;	
		}
		i++;
	}
	return (valid);
}

int	is_idf_exist(t_env *list, char *idf)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, idf, ft_strlen_g(idf)))
			return (0);
		tmp = tmp->next;	
	}
	return (1);
}

int	add_env(t_env **list, char *idf)
{
	t_env	*newList;
	t_env	*current;

    newList = parseAndCreateEnvList(idf);
    if (!newList)
        return (1);
    if (*list == NULL) 
	{
        *list = newList; 
        return (0);
    }
    current = *list;
    while (current->next != NULL)
        current = current->next;
    current->next = newList;
    return (0);
}

int	change_envp(t_env	*list, char *idf)
{
	if (!is_idf_exist(list, idf))
	{
		
	}
	if (!add_env(&list, idf))
		return (1);
	return (0);
}

int	builtin_export(t_env *list, char	**cmd)
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
		{
			
		}
		i++;
	}
	return (exit_status);
}
