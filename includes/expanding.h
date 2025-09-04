/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:14:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/04 12:03:11 by yingzhan         ###   ########.fr       */
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

void	print_exp(t_node *node);
void	ft_expand(t_node *root, t_shell *shell);

#endif