/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:52:46 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 20:18:18 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_variable(int quote, char *s)
{
	if (quote == q_dopen && s[0] == '$' && (s[1] == '_' \
		|| s[1] == '?' || ft_isalpha(s[1])))
		return (1);
	else if (quote == q_close && s[0] == '$' \
		&& (s[1] == '_' || s[1] == '?' || ft_isalpha(s[1])))
		return (1);
	else
		return (0);
}

static int	add_var(char **s, char **value, t_shell *shell, t_token **list)
{
	char	*var;
	char	*tmp;

	var = handle_dollar(s, shell, list);
	if (!var)
		clean_tokens(list, 1);
	tmp = ft_strjoin(*value, var);
	if (!tmp)
		clean_tokens(list, 1);
	free (var);
	free (*value);
	*value = tmp;
	return ((int)ft_strlen(*value));
}

static int	break_condition(int quote, char c)
{
	if (!quote)
	{
		if ((!c || c == ' ' || (c >= '\t' && c <= '\r')) || ft_strchr("|><", c))
			return (1);
	}
	return (0);
}

static char	*add_word(char **s, int *quote, t_token **list, t_shell *shell)
{
	int		pos;
	char	*value;

	pos = 0;
	value = NULL;
	while (*(*s))
	{
		if (*(*s) == '\'' || *(*s) == '"')
			(*s) += change_quote(*(*s), quote);
		if (*quote || (!*quote && *(*s) != '\'' && *(*s) != '"'))
		{
			if (break_condition(*quote, *(*s)))
				break ;
			if (is_variable(*quote, *s))
				pos = add_var(s, &value, shell, list);
			else
			{
				ft_realloc(pos, *(*s), &value, list);
				pos++;
				(*s)++;
			}
		}
	}
	return (value);
}

int	handle_words(char *s, int *quote, t_token **list, t_shell *shell)
{
	char	*start;
	char	*value;

	start = s;
	value = add_word(&s, quote, list, shell);
	add_tokens(list, T_WORD, value);
	return (s - start);
}
