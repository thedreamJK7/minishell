/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:49:28 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 20:32:40 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//This is a clean function for end of grogram
void	clean_tokens(t_token **list, int exit_flag)
{
	t_token	*tmp;

	if (!list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->value)
			free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (exit_flag)
		exit(1);
}
