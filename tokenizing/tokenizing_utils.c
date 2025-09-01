/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:53:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/01 16:09:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Add new nodes to the back of link list
void	add_tokens(t_token **list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		clean_tokens(list, 1);
	}
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

void	specify_tokens_single(char **value, char c, t_token **list)
{
	if (c == '|')
	{
		*value = ft_strdup("|");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_PIPE, *value);
	}
	else if (c == '<')
	{
		*value = ft_strdup("<");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_LESS, *value);
	}
	else if (c == '>')
	{
		*value = ft_strdup(">");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_GREAT, *value);
	}
}

int	specify_tokens_double(char **value, char c, t_token **list)
{
	if (c == '<')
	{
		*value = ft_strdup("<<");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_DLESS, *value);
	}
	else if (c == '>')
	{
		*value = ft_strdup(">>");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_DGREAT, *value);
	}
	else if (c == '|')
	{
		specify_tokens_single(value, c, list);
		return (1);
	}
	return (2);
}

static void	ft_realloc(int pos, char c, char **value, t_token **list)
{
	char	*tmp;
	int		i;

	tmp = malloc(pos + 2);
	if (!tmp)
	{
		free(*value);
		*value = NULL;
		clean_tokens(list, 1);
	}
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

void	add_word(char **s, int *quote, t_token **list, char **value)
{
	int		pos;

	pos = 0;
	while (*(*s))
	{
		if (*(*s) == '\'' || *(*s) == '"')
			(*s) += change_quote(*(*s), quote);
		if (!*quote && *(*s) != '\'' && *(*s) != '"')
		{
			if (!*(*s) || *(*s) == ' ' || (*(*s) >= '\t' && *(*s) <= '\r') \
			|| ft_strchr("|><", *(*s)))
				return ;
			ft_realloc(pos, *(*s), value, list);
			pos++;
		}
		else if (*quote)
		{
			if (*quote == q_dopen && *(*s) == '$')
				return ;
			ft_realloc(pos, *(*s), value, list);
			pos++;
		}
		(*s)++;
	}
}
