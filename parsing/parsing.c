/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:14:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/22 13:32:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenize(char *s)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (!s[i])
			break ;
		if (ft_strchr("|><", s[i]) && s[i + 1] && s[i + 1] == s[i])
			i += specify_tokens(s[i], &list, 0);
		else if (ft_strchr("|><", s[i]) && !(s[i + 1] && s[i + 1] == s[i]))
			i += specify_tokens(s[i], &list, 1);
		else if (ft_strchr("'\"", s[i]))
			i += handle_quotes(s + i, s[i], &list);
		else
			i += handle_words(s + i, &list);
	}
	print_tokens(list);
	clean_tokens(&list);
}
