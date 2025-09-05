/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:51:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 19:50:05 by yingzhan         ###   ########.fr       */
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
