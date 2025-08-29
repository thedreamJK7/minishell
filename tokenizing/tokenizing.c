/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:19:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/29 13:20:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int	handle_quotes(char *s, char c, t_token **list)
{
	char	*end_quote;
	char	*value;

	end_quote = ft_strchr(s + 1, (int)c);
	if (!end_quote)
		return (1);
	value = ft_substr(s, 0, end_quote - s + 1);
	if (!value)
	{
		clean_tokens(list);
		exit(1);
	}
	add_tokens(list, T_WORD, value);
	return (end_quote - s + 1);
}*/

int	change_quote(char c, int *quote)
{
	if (c == '\'')
	{
		if (*quote == q_sopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_sopen;
	}
	else if (c == '"')
	{
		if (*quote == q_dopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_dopen;
	}
	return (1);
}

void	ft_realloc(int pos, char c, char **value)
{
	char	*tmp;
	int		i;

	tmp = malloc(pos + 2);
//	if (!tmp)
//		return (NULL);
	i = 0;
	while (i < pos)
	{
		tmp[i] = (*value)[i];
		i++;
	}
	tmp[pos] = c;
	tmp[pos + 1] = 0;
	free (*value);
	*value = tmp;
}

int	handle_words(char *s, int quote, t_token **list)
{
	char	*start;
	int		pos;
	char	*value;

	value = NULL;
	start = s;
	pos = 0;
	while(*s)
	{
		if (*s == '\'' || *s == '"')
			s += change_quote(*s, &quote);
		if (!quote && *s != '\'' && *s != '"')
		{
			if (!*s || *s == ' ' || (*s >= '\t' && *s <= '\r') || ft_strchr("|><", *s))
			{
				add_tokens(list, T_WORD, value);
				return (s - start);
			}
			ft_realloc(pos, *s, &value);
			pos++;
		}
		else if (quote && *s != '\'' && *s != '"')
		{
			ft_realloc(pos, *s, &value);
			pos++;
		}
		s++;
	}
	add_tokens(list, T_WORD, value);
	return (s - start);
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
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '"')
			i += change_quote(s[i], &quote);
		if (!quote && ft_strchr("|><", s[i]) && s[i + 1] && s[i + 1] == s[i])
			i += specify_tokens(s[i], &list, 0);
		else if (!quote && ft_strchr("|><", s[i]) && !(s[i + 1] && s[i + 1] == s[i]))
			i += specify_tokens(s[i], &list, 1);
		else if ((!quote || quote == q_dopen) && s[i] == '$')
			i += handle_dollar(s + i, &list, quote);
		else
			i += handle_words(s + i, quote, &list);
	}
	add_tokens(&list, T_EOF, NULL);
	print_tokens(list);//should be removed later
	return (list);
}
