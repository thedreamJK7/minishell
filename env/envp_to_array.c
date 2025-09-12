/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:00:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/12 10:33:33 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_envp_list(t_env *env_list)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env_list;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

char	*env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, '=');
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	if (!result)
		return (free(temp), NULL);
	return (result);
}

int	fill_array(char **arr, t_env *env_list)
{
	t_env	*current;
	int		i;

	i = 0;
	current = env_list;
	while (current)
	{
		arr[i] = env_string(current->name, current->value);
		if (!arr[i])
			
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return(arr);
}

char	**envp_to_array(t_env *env_list)
{
	char	**arr;
	int		count;

	count = count_envp_list(env_list);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	if (!fill_array(arr, env_list))
	{
		free_commands(arr);
		return (NULL);
	}
	return (arr);
}