/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/21 21:07:37 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	specify_token(char c, t_token *list, int single)
{
	if (!single)
	{
		if (c == '<')
			add_token(&list, T_DLESS, "<<");
		else if (c == '>')
			add_token(&list, T_DGREAT, ">>");
	}
	else
	{
		if (c == '|')
			add_token(&list, T_PIPE, "|");
		else if (c == '<')
			add_token(&list, T_LESS, "<");
		else if (c == '>')
			add_token(&list, T_GREAT, ">");
	}
}

int	handle_quotes(char *s, char c, t_token *list)
{
	char	*end;
	char	*start;
	int		len;

	start = s + 1;
	end = ft_strchr(start, (int)c) - 1;
	add_token(&list, T_WORD, ft_substr(s, 0, end - start + 1));
	len = end - start + 3;
	return (len);
}

int	handle_word(char *s, t_token *list)
{
	char	*end;
	char	*start;
	int		len;

	start = s;
	end = ft_strchr(start, 32) - 1;
	add_token(&list, T_WORD, ft_substr(s, 0, end - start + 1));
	len = end - start + 1;
	return (len);
}

t_token	*ft_tokenize(char *s)
{
	t_token	*list;
	int		i;
	int		j;

	list = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (ft_strchr("|><", s[i]))
		{
			if (s[i + 1] == s[i])
			{
				specify_token(s[i], list, 0);
				i += 2;
			}
			else
			{
				specify_token(s[i], list, 1);
				i += 1;
			}
		}
		else if (s[i] == '"' || s[i] == "'")
			i += handle_quotes(s + i, s[i], list);
		else
			i += handle_word(s, list);
	}
}
