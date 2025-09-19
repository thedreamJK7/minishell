/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:19:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/18 16:44:00 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_tokenize(char *s, t_shell *shell)
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
		if (s[i] && s[i] != ' ' && !(s[i] >= '\t' && s[i] <= '\r') && !(ft_strchr("|><", s[i]) && !quote))
			i += handle_words(s + i, &quote, &list, shell);
	}
	add_tokens(&list, T_EOF, NULL);
	return (list);
}
