/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:53:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/08 12:03:10 by jkubaev          ###   ########.fr       */
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

void	ft_realloc(int pos, char c, char **value, t_token **list)
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
	*value = tmp;
}
