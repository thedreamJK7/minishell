/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:15:26 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/12 13:17:43 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	appendEnvList(t_env **head, t_env **tail, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

t_env	*newListF(char *name, char *value)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->name = name;
	new_list->value = value;
	new_list->next = NULL;
	return (new_list);
}

t_env	*parseAndCreateEnvList(const char *envp)
{
	t_env	*newList;
	char	*name;
	char	*value;
	char	*equalSign;

	equalSign = ft_strchr(envp, '=');
	if (!equalSign)
		return (NULL);
	name = ft_substr(envp, 0, equalSign - envp);
	if (!name)
		return (NULL);
	value = ft_strdup(equalSign + 1);
	if (!value)
		return (free(name), NULL);
	newList = newListF(name, value);
	if (!newList)
		return (free(name), free(value), NULL);
	return (newList);
}

t_env *init_envp_list(char **envp)
{
	t_env	*new_list;
	t_env	*head;
	t_env	*tail;
	int		i;

	i = 0;
	new_list = NULL;
	head = NULL;
	tail = NULL;
	while (envp[i])
	{
		new_list = parseAndCreateEnvList(envp[i]);
		if (!new_list)
			return (freeEnvList(head), NULL);
		appendEnvList(&head, &tail, new_list);
		i++;
	}
	return (head);
}

t_shell	*init_envp(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_list = init_envp_list(envp);
	if (!shell->env_list)
		return (free(shell), NULL);
	shell->exit_code = 0;
	return (shell);
}