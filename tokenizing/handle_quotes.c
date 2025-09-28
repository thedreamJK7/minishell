/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:14:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/27 16:56:28 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_quote(char c, int *quote)
{
	if (c == '\'')
	{
		if (*quote == q_sopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_sopen;
		else
			return (0);
	}
	else if (c == '"')
	{
		if (*quote == q_dopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_dopen;
		else
			return (0);
	}
	return (1);
}
