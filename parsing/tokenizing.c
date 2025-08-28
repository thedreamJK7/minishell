/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:53:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/08/27 18:04:03 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Add new nodes to the back of link list
void	add_tokens(t_token **list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	if (!value && type != T_EOF)
	{
		clean_tokens(list);
		exit(1);
	}
	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		clean_tokens(list);
		exit(1);
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

//Specify special tokens and add to the list
int	specify_tokens(char c, t_token **list, int single)
{
	char	*value;

	if (!single)
	{
		if (c == '<')
		{
			value = ft_strdup("<<");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_DLESS, value);
		}
		else if (c == '>')
		{
			value = ft_strdup(">>");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_DGREAT, value);
		}
		else
		{
			value = ft_strdup("|");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_PIPE, value);
		}
		return (2);
	}
	else
	{
		if (c == '|')
		{
			value = ft_strdup("|");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_PIPE, value);
		}
		else if (c == '<')
		{
			value = ft_strdup("<");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_LESS, value);
		}
		else if (c == '>')
		{
			value = ft_strdup(">");
			if (!value)
			{
				clean_tokens(list);
				exit(1);
			}
			add_tokens(list, T_GREAT, value);
		}
		return (1);
	}
}

//Interpret quotation marks and add to list
//Unclosed quotation marks treated as normal words until seperated by special tokens
int	handle_quotes(char *s, char c, t_token **list)
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
}

//Interpret normal words and add to list
//Backslash and semicolon treated as normal words
int	handle_words(char *s, t_token **list)
{
	char	*end;
	char	*value;

	end = s;
	while (*end && !(*end == ' ' || (*end >= '\t' && *end <= '\r')) && !ft_strchr("|><'\"", *end))
		end++;
	value = ft_substr(s, 0, end - s);
	if (!value)
	{
		clean_tokens(list);
		exit(1);
	}
	add_tokens(list, T_WORD, value);
	return (end - s);
}

//This is a clean function for end of grogram
void	clean_tokens(t_token **list)
{
	t_token	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

//This is a test function for ft_tokenize (which will be deleted later)
void	print_tokens(t_token *list)
{
	t_token *tmp;

	tmp = list;
	while (tmp)
	{
		printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}