/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:19:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/04 15:57:04 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_quote(char c, int *quote)
{
	if (c == '\'')
	{
		if (*quote == q_sopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_sopen;
		else
			return (0);
	}
	else if (c == '"')
	{
		if (*quote == q_dopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_dopen;
		else
			return (0);
	}
	return (1);
}

//Specify special tokens and add to the list
int	specify_tokens(char *s, t_token **list)
{
	char	*value;

	value = NULL;
	if (*(s + 1) && *(s + 1) == *s)
		return (specify_tokens_double(&value, *s, list));
	else
	{
		specify_tokens_single(&value, *s, list);
		return (1);
	}
}

int	handle_words(char *s, int *quote, t_token **list)
{
	char	*start;
	char	*value;

	start = s;
	value = NULL;
	add_word(&s, quote, list, &value);
	add_tokens(list, T_WORD, value);
	return (s - start);
}

//Interpret $ and add to list
//Only [a-zA-Z_][a-zA-Z0-9_] is treated as valid t_var without $ sign
//Otherwise taken as t_word
int	handle_dollar(char *s, t_token **list, int quote)
{
	char	*value;
	int		i;

	i = 1;
	if (!s[i])
		return (handle_words(s, &quote, list));
	if (s[i] == '?')
	{
		value = ft_strdup("?");
		add_tokens(list, T_VAR, value);
		return (2);
	}
	else if (s[i] == '_' || ft_isalpha(s[i]))
	{
		while (s[i + 1] == '_' || ft_isalnum(s[i + 1]))
			i++;
		value = ft_substr(s, 1, i);
		add_tokens(list, T_VAR, value);
		return (i + 1);
	}
	else
		return (handle_words(s, &quote, list));
}

t_token	*ft_tokenize(char *s)
{
	t_token	*list;
	int		i;
	int		quote;

	list = NULL;
	quote = q_close;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (s[i] == '\'' || s[i] == '"')
			i += change_quote(s[i], &quote);
		if (s[i] && !quote && ft_strchr("|><", s[i]))
			i += specify_tokens(s + i, &list);
		else if ((!quote || quote == q_dopen) && s[i] == '$')
			i += handle_dollar(s + i, &list, quote);
		else if (s[i] && s[i] != ' ' && !(s[i] >= '\t' && s[i] <= '\r'))
			i += handle_words(s + i, &quote, &list);
	}
	add_tokens(&list, T_EOF, NULL);
	//print_tokens(list);//should be removed later
	return (list);
}
