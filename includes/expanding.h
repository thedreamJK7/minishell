/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:14:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 14:43:32 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "parsing.h"

typedef struct s_shell
{
	char	**env;
	int		exit_code;
}	t_shell;

//void	print_exp(t_node *node);
//void	ft_expand(t_node *root, t_shell *shell);

#endif