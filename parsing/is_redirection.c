/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isRedirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:29:23 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/04 12:00:02 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == T_LESS || type == T_GREAT || type == T_DLESS 
		|| type == T_DGREAT);
}
