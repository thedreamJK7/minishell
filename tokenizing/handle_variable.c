/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:51:42 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 20:08:24 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_getenv(t_shell *shell, char *s)
{
	int		i;
	int		len;

	if (!shell || !shell->env || !s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (shell->env[i])
	{
		if (!ft_strncmp(s, shell->env[i], len) && shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
		i++;
	}
	return (NULL);
}

static char	*expand_var(char *s, t_shell *shell, t_token **list)
{
	char	*var;
	char	*value;

	var = NULL;
	if (!ft_strncmp(s, "?", 1))
		value = ft_itoa(shell->exit_code);
	else
	{
		var = ft_getenv(shell, s);
		if (!var)
			value = ft_strdup("");
		else
			value = ft_strdup(var);
	}
	if (!value)
		clean_tokens(list, 1);
	return (value);
}

//Interpret $ and expand
//Only [a-zA-Z_][a-zA-Z0-9_] is treated as valid t_var without $ sign
//Otherwise taken as t_word
char	*handle_dollar(char **s, t_shell *shell, t_token **list)
{
	char	*value;
	int		i;
	char	*var;

	i = 1;
	value = NULL;
	if ((*s)[i] == '?')
	{
		value = expand_var("?", shell, list);
		(*s) += 2;
	}
	else if ((*s)[i] == '_' || ft_isalpha((*s)[i]))
	{
		while ((*s)[i + 1] == '_' || ft_isalnum((*s)[i + 1]))
			i++;
		var = ft_substr((*s), 1, i);
		if (!var)
			clean_tokens(list, 1);
		value = expand_var(var, shell, list);
		free (var);
		(*s) += i + 1;
	}
	return (value);
}
