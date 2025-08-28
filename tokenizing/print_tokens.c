/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javokhir <javokhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:01:01 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/27 22:01:49 by javokhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//This is a test function for ft_tokenize (which will be deleted later)
void	print_tokens(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("Type: %d, Value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}
