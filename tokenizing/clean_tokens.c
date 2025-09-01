/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:42:40 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/01 16:07:37 by yingzhan         ###   ########.fr       */
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
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (exit_flag)
		exit(1);
}
